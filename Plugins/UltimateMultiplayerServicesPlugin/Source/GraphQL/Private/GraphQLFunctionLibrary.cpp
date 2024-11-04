/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, October 2020
 */

#include "GraphQLFunctionLibrary.h"

#include "GraphQLGlobals.h"

#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"
#include "WebSocketsModule.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/Base64.h"
#include "Misc/CString.h"
#include "Containers/UnrealString.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "TimerManager.h"

#if PLATFORM_WINDOWS
#include "Windows/WindowsPlatformCompilerPreSetup.h"
#include "Windows/WindowsHWrapper.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#endif

#if PLATFORM_ANDROID
#include "Android/AndroidPlatformCompilerPreSetup.h"
#endif

#if PLATFORM_IOS
#include "IOS/IOSPlatformCompilerPreSetup.h"
#endif

#if PLATFORM_MAC
#include "Mac/MacPlatformCompilerPreSetup.h"
#endif

#if PLATFORM_APPLE
#include "Apple/ApplePlatformCompilerPreSetup.h"
#endif

#if PLATFORM_LINUX
#include "Linux/LinuxPlatformCompilerPreSetup.h"
#endif

#if PLATFORM_UNIX
#include "Unix/UnixPlatformCompilerPreSetup.h"
#endif

#define UI UI_ST
THIRD_PARTY_INCLUDES_START
#include "openssl/sha.h"
#include "openssl/hmac.h"
#include "openssl/ossl_typ.h"
THIRD_PARTY_INCLUDES_END
#undef UI

#if PLATFORM_WINDOWS
#include "Windows/HideWindowsPlatformTypes.h"
#endif

#include "Runtime/Engine/Classes/Engine/Engine.h"

#include "LatentActions.h"

#include <string>

#define KeepAliveTimeoutThreshold 5

FString GetSHA256HEXSignature(const FString &str) {
    unsigned char *hash = new unsigned char[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    const FTCHARToUTF8 Converter(*str, str.Len());

    SHA256_Update(&sha256, reinterpret_cast<const uint8*>(Converter.Get()), Converter.Length());

    SHA256_Final(hash, &sha256);
    return BytesToHex(hash, SHA256_DIGEST_LENGTH).ToLower();
}

const std::string GetHMACSHA256Signature(const std::string key, const std::string msg) {
    unsigned char *c_key = new unsigned char[key.length() + 1];
    memcpy(c_key, (unsigned char *)key.data(), key.length());

    unsigned char *c_msg = new unsigned char[msg.length() + 1];
    memcpy(c_msg, (unsigned char *)msg.data(), msg.length());

    unsigned char * digest = HMAC(EVP_sha256(), (unsigned char*)c_key, key.length(), c_msg, msg.length(), NULL, NULL);

    delete[] c_key;
    delete[] c_msg;

    std::string signed_str = std::string((char *)digest, SHA256_DIGEST_LENGTH);

    return signed_str;
}

FString GetHMACSHA256HEXSignature(const std::string key, const std::string msg) {
    unsigned char *c_key = new unsigned char[key.length() + 1];
    memcpy(c_key, (unsigned char *)key.data(), key.length());

    unsigned char *c_msg = new unsigned char[msg.length() + 1];
    memcpy(c_msg, (unsigned char *)msg.data(), msg.length());

    unsigned char * digest = HMAC(EVP_sha256(), (unsigned char*)c_key, key.length(), c_msg, msg.length(), NULL, NULL);

    delete[] c_key;
    delete[] c_msg;
    
    return BytesToHex(digest, SHA256_DIGEST_LENGTH).ToLower();
}

class FConnectAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;
    bool &success;
    FString &errors;

public:
    FConnectAction(
            TSharedPtr < IWebSocket > socket,
            bool &success,
            FString &errors,
            const FLatentActionInfo &LatentInfo
    ) :
            ExecutionFunction(LatentInfo.ExecutionFunction),
            OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget), success(success), errors(errors) {
        socket->Connect();
    }

    void Complete(bool bIsSuccess, FString errorsMessage) {
        completed = true;
        success = bIsSuccess;
        errors = errorsMessage;
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("Send GraphQL Request");
    }

#endif
};

void USubscriptionHandler::OnGraphQLError_Implementation(const FString& id, const FString& errors) {
}

void USubscriptionHandler::OnGraphQLConnectionError_Implementation(const FString& errors) {
}

void USubscriptionHandler::OnConnected_Implementation() {
    if (this->gameInstance == nullptr) {
        this->gameInstance = dynamic_cast<UGameInstance*>(GetOuter());
    }
        
    this->sendConnectionInitRequest();
}

void USubscriptionHandler::OnConnectionError_Implementation(const FString& errors) {
    this->connectAction->Complete(false, errors);
}

void USubscriptionHandler::OnClosed_Implementation(int32 StatusCode, const FString& Reason, bool bWasClean) {
}

void USubscriptionHandler::OnKeepAliveMessageMissed_Implementation() {
    this->disconnect(4000, FString("didn't receive keep alive message on time"));
}

void USubscriptionHandler::OnReceiveStartACKMessage_Implementation(const FString& id) {
}

void USubscriptionHandler::OnReceiveCompleteMessage_Implementation(const FString& id) {
}

void USubscriptionHandler::OnReceiveDataMessage_Implementation(const FString& id, const FString& data) {
}

bool USubscriptionHandler::sendConnectionInitRequest() {
    if (this->socket.IsValid() && this->socket->IsConnected()) {
        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        JsonObject->SetStringField("type", "connection_init");
        FString data;
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&data);
        FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
        this->socket->Send(data);
        return true;
    } else {
        LOG_GRAPHQL_WARNING("Subscribe GraphQL Subscription is not called or socket is not connected");
        return false;
    }
}

class FSendStartSubscriptionRequestAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;
    bool &success;
    FString &errors;

public:
    FSendStartSubscriptionRequestAction(
            TSharedPtr < IWebSocket > socket,
            bool &success,
            FString id,
            FString query,
            FString variables,
            TMap<FString, FString> authorization,
            FString &errors,
            const FLatentActionInfo &LatentInfo
    ) :
            ExecutionFunction(LatentInfo.ExecutionFunction),
            OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget), success(success), errors(errors) {
        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        JsonObject->SetStringField("type", "start");
        JsonObject->SetStringField("id", id);

        TSharedPtr<FJsonObject> payloadJsonObject = MakeShareable(new FJsonObject());

        {
            TSharedPtr<FJsonObject> dataJsonObject = MakeShareable(new FJsonObject());
            dataJsonObject->SetStringField("query", query);
            if (!variables.IsEmpty()) {
                TSharedPtr<FJsonObject> variablesJsonObject;
                TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(variables);
                if (FJsonSerializer::Deserialize(Reader, variablesJsonObject)) {
                    dataJsonObject->SetObjectField("variables", variablesJsonObject);
                } else {
                    LOG_GRAPHQL_WARNING("variables cannot be deserialized.");
                }
            } else {
                variables = FString("{}");
                TSharedPtr<FJsonObject> variablesJsonObject;
                TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(variables);
                if (FJsonSerializer::Deserialize(Reader, variablesJsonObject)) {
                    dataJsonObject->SetObjectField("variables", variablesJsonObject);
                } else {
                    LOG_GRAPHQL_WARNING("\"{}\" cannot be deserialized.");
                }
            }

            FString data;
            TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&data);
            FJsonSerializer::Serialize(dataJsonObject.ToSharedRef(), Writer);

            payloadJsonObject->SetStringField("data", data);
        }

        {
            TSharedPtr<FJsonObject> extensionsJsonObject = MakeShareable(new FJsonObject());

            {
                TSharedPtr<FJsonObject> authorizationJsonObject = MakeShareable(new FJsonObject());
                for (const TPair<FString, FString>& elem : authorization) {
                    authorizationJsonObject->SetStringField(elem.Key, elem.Value);
                }

                extensionsJsonObject->SetObjectField("authorization", authorizationJsonObject);
            }

            payloadJsonObject->SetObjectField("extensions", extensionsJsonObject);
        }

        JsonObject->SetObjectField("payload", payloadJsonObject);
        FString data;
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&data);
        FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
        socket->Send(data);
    }
    
    void Complete(bool bIsSuccess, FString errorsMessage) {
        completed = true;
        success = bIsSuccess;
        errors = errorsMessage;
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("Send GraphQL Request");
    }

#endif
};

bool USubscriptionHandler::sendStartSubscriptionRequest(
        UObject *WorldContextObject,
        bool &success,
        FString id,
        FString query,
        FString variables,
        TMap<FString, FString> authorization,
        FString &errors,
        struct FLatentActionInfo LatentInfo
) {
    if (this->socket.IsValid() && this->socket->IsConnected()) {
        if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
            FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
            if (LatentActionManager.FindExistingAction<FSendStartSubscriptionRequestAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
                FSendStartSubscriptionRequestAction *action = new FSendStartSubscriptionRequestAction(
                        this->socket,
                        success,
                        id,
                        query,
                        variables,
                        authorization,
                        errors,
                        LatentInfo
                );
                
                this->sendStartSubscriptionRequestActions.Add(id, action);
                LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, action);
            }
        }
        return true;
    } else {
        LOG_GRAPHQL_WARNING("Subscribe GraphQL Subscription is not called or socket is not connected");
        return false;
    }
}

class FSendStopSubscriptionRequestAction : public FPendingLatentAction {
private:
    // trigger for finish
    bool completed = false;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;
    bool &success;
    FString &errors;

public:
    FSendStopSubscriptionRequestAction(
            TSharedPtr < IWebSocket > socket,
            bool &success,
            FString id,
            FString &errors,
            const FLatentActionInfo &LatentInfo
    ) :
            ExecutionFunction(LatentInfo.ExecutionFunction),
            OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget), success(success), errors(errors) {
        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        JsonObject->SetStringField("type", "stop");
        JsonObject->SetStringField("id", id);
        FString data;
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&data);
        FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
        socket->Send(data);
    }

    void Complete(bool bIsSuccess, FString errorsMessage) {
        completed = true;
        success = bIsSuccess;
        errors = errorsMessage;
    }

    void UpdateOperation(FLatentResponse &Response) override {
        Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("Send GraphQL Request");
    }

#endif
};

bool USubscriptionHandler::sendStopSubscriptionRequest(
        UObject *WorldContextObject,
        bool &success,
        FString id,
        FString &errors,
        struct FLatentActionInfo LatentInfo
) {
    if (this->socket.IsValid() && this->socket->IsConnected()) {
        if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
            FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
            if (LatentActionManager.FindExistingAction<FSendStopSubscriptionRequestAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
                FSendStopSubscriptionRequestAction *action = new FSendStopSubscriptionRequestAction(
                        this->socket,
                        success,
                        id,
                        errors,
                        LatentInfo
                );

                this->sendStopSubscriptionRequestActions.Add(id, action);
                LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, action);
            }
        }
        return true;
    } else {
        LOG_GRAPHQL_WARNING("Subscribe GraphQL Subscription is not called or socket is not connected");
        return false;
    }
}

void USubscriptionHandler::connect(
        UObject *WorldContextObject,
        bool &success,
        FString &errors,
        struct FLatentActionInfo LatentInfo
) {
    if (this->socket->OnConnected().IsBound()) {
        this->socket->OnConnected().Clear();
    }

    if (this->socket->OnConnectionError().IsBound()) {
        this->socket->OnConnectionError().Clear();
    }

    if (this->socket->OnClosed().IsBound()) {
        this->socket->OnClosed().Clear();
    }

    if (this->socket->OnMessage().IsBound()) {
        this->socket->OnMessage().Clear();
    }

    if (this->keepAliveTimerHandler.IsValid()) {
        this->gameInstance->GetTimerManager().ClearTimer(this->keepAliveTimerHandler);
    }

    this->socket->OnConnected().AddLambda([this]() {
        this->OnConnected();
    });

    this->socket->OnConnectionError().AddLambda([this](const FString& error) {
        this->OnConnectionError(error);
    });

    this->socket->OnClosed().AddLambda([this](int32 StatusCode, const FString& Reason, bool bWasClean) {
        this->OnClosed(StatusCode, Reason, bWasClean);
    });

    this->socket->OnMessage().AddLambda([this](const FString& message) {
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(message);
        if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
            messageFailedToDeserialize = FString("");
            this->handleMessage(JsonObject);
        } else {
            LOG_GRAPHQL_WARNING("message cannot be deserialized. message: " + message);
            messageFailedToDeserialize = messageFailedToDeserialize
                    .Append(message);
            LOG_GRAPHQL_NORMAL("try again with combined message: " + message);
            Reader = TJsonReaderFactory<>::Create(messageFailedToDeserialize);
            if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
                messageFailedToDeserialize = FString("");
                this->handleMessage(JsonObject);
            }
        }
    });

    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FConnectAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            this->connectAction = new FConnectAction(
                    this->socket,
                    success,
                    errors,
                    LatentInfo
            );
            
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, this->connectAction);
        }
    }
}

void USubscriptionHandler::handleMessage(TSharedPtr<FJsonObject> JsonObject) {
    if (JsonObject->HasTypedField<EJson::String>("type")) {
        FString messageType = JsonObject->GetStringField("type");

        if (messageType.Equals(FString("connection_error"), ESearchCase::Type::CaseSensitive)) {
            if (JsonObject->HasTypedField<EJson::Object>("payload")) {
                TSharedPtr<FJsonObject> connectionErrorPayload = JsonObject->GetObjectField("payload");

                FString errors;
                TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&errors);
                FJsonSerializer::Serialize(connectionErrorPayload.ToSharedRef(), Writer);

                if (this->connectAction != nullptr) {
                    this->connectAction->Complete(false, "connection failed");
                }
                
                this->OnGraphQLConnectionError(errors);

            } else {
                LOG_GRAPHQL_WARNING("no payload field in connection error message.");
            }
        } else if (messageType.Equals(FString("error"), ESearchCase::Type::CaseSensitive)) {
            if (JsonObject->HasTypedField<EJson::Object>("payload")) {
                TSharedPtr<FJsonObject> errorPayload = JsonObject->GetObjectField("payload");

                FString errors;
                TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&errors);
                FJsonSerializer::Serialize(errorPayload.ToSharedRef(), Writer);

                FString id;
                if (JsonObject->HasTypedField<EJson::String>("id")) {
                    id = JsonObject->GetStringField("id");
                    
                    if (this->sendStartSubscriptionRequestActions.Contains(id)) {
                        FSendStartSubscriptionRequestAction * action = this->sendStartSubscriptionRequestActions[id];
                        
                        if (action != nullptr) {
                            action->Complete(false, errors);
                        }
                    }
                    
                    if (this->sendStopSubscriptionRequestActions.Contains(id)) {
                        FSendStopSubscriptionRequestAction * action = this->sendStopSubscriptionRequestActions[id];
                        
                        if (action != nullptr) {
                            action->Complete(false, errors);
                        }
                    }
                }

                this->OnGraphQLError(id, errors);

            } else {
                LOG_GRAPHQL_WARNING("no payload field in error message.");
            }
        } else if (messageType.Equals(FString("connection_ack"), ESearchCase::Type::CaseSensitive)) {
            if (JsonObject->HasTypedField<EJson::Object>("payload")) {
                TSharedPtr<FJsonObject> connectionAckPayload = JsonObject->GetObjectField("payload");

                if (this->gameInstance == nullptr) {
                    LOG_GRAPHQL_WARNING("game instance is not set in construction");

                    if (this->connectAction != nullptr) {
                        this->connectAction->Complete(false, "game instance is missing");
                    }
                    
                    return;
                }
                
                if (connectionAckPayload->HasTypedField<EJson::Number>("connectionTimeoutMs")) {
                    double timeout = connectionAckPayload->GetNumberField("connectionTimeoutMs");
                    this->gameInstance->GetTimerManager().SetTimer(
                            this->keepAliveTimerHandler,
                            [this]() {
                                if (this->keepAlive) {
                                    this->keepAlive = false;
                                } else {
                                    this->OnKeepAliveMessageMissed();
                                }
                            },
                            (float) timeout / 1000 + KeepAliveTimeoutThreshold,
                            true
                    );

                    if (this->connectAction != nullptr) {
                        this->connectAction->Complete(true, "");
                    }
                } else if (connectionAckPayload->HasTypedField<EJson::Number>("connectionTimeout")) {
                    double timeout = connectionAckPayload->GetNumberField("connectionTimeout");
                    this->gameInstance->GetTimerManager().SetTimer(
                            this->keepAliveTimerHandler,
                            [this]() {
                                if (this->keepAlive) {
                                    this->keepAlive = false;
                                } else {
                                    this->OnKeepAliveMessageMissed();
                                }
                            },
                            (float) timeout / 1000 + KeepAliveTimeoutThreshold,
                            true
                    );

                    if (this->connectAction != nullptr) {
                        this->connectAction->Complete(true, "");
                    }
                } else {
                    FString payload;
                    TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&payload);
                    FJsonSerializer::Serialize(connectionAckPayload.ToSharedRef(), Writer);
                    LOG_GRAPHQL_WARNING("no connection timeout field in connection ack payload. message: " + payload);
                    
                    if (this->connectAction != nullptr) {
                        this->connectAction->Complete(false, "connection timeout field not found");
                    }
                }
            } else {
                LOG_GRAPHQL_WARNING("no payload field in connection ack message.");

                if (this->connectAction != nullptr) {
                    this->connectAction->Complete(false, "no payload field in connection ack message");
                }
            }
        } else if (messageType.Equals(FString("ka"), ESearchCase::Type::CaseSensitive)) {
            this->keepAlive = true;
        } else if (messageType.Equals(FString("start_ack"), ESearchCase::Type::CaseSensitive)) {
            FString id;
            if (JsonObject->HasTypedField<EJson::String>("id")) {
                id = JsonObject->GetStringField("id");
                
                if (this->sendStartSubscriptionRequestActions.Contains(id)) {
                    FSendStartSubscriptionRequestAction * action = this->sendStartSubscriptionRequestActions[id];

                    if (action != nullptr) {
                        action->Complete(true, FString(""));
                    }
                }
                
                this->OnReceiveStartACKMessage(id);
            } else {
                LOG_GRAPHQL_WARNING("no id field in start ack message.");
            }
        } else if (messageType.Equals(FString("complete"), ESearchCase::Type::CaseSensitive)) {
            FString id;
            if (JsonObject->HasTypedField<EJson::String>("id")) {
                id = JsonObject->GetStringField("id");
                
                if (this->sendStopSubscriptionRequestActions.Contains(id)) {
                    FSendStopSubscriptionRequestAction * action = this->sendStopSubscriptionRequestActions[id];

                    if (action != nullptr) {
                        action->Complete(true, FString(""));
                    }
                }
                
                this->OnReceiveCompleteMessage(id);
            } else {
                LOG_GRAPHQL_WARNING("no id field in complete message.");
            }
        } else if (messageType.Equals(FString("data"), ESearchCase::Type::CaseSensitive)) {
            if (JsonObject->HasTypedField<EJson::Object>("payload")) {
                TSharedPtr<FJsonObject> dataPayload = JsonObject->GetObjectField("payload");

                FString data;
                TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&data);
                FJsonSerializer::Serialize(dataPayload.ToSharedRef(), Writer);

                FString id;
                if (JsonObject->HasTypedField<EJson::String>("id")) {
                    id = JsonObject->GetStringField("id");
                    this->OnReceiveDataMessage(id, data);
                } else {
                    LOG_GRAPHQL_WARNING("no id field in complete message.");
                }
            } else {
                LOG_GRAPHQL_WARNING("no payload field in error message.");
            }
        } else {
            LOG_GRAPHQL_WARNING(FString::Printf(TEXT("unknown type field in message. type: %s"), *messageType));
        }
    } else {
        LOG_GRAPHQL_WARNING("no type field in message.");
    }
}

void USubscriptionHandler::disconnect(int32 Code, const FString& Reason) {
    this->socket->Close(Code, Reason);

    if (this->socket->OnConnected().IsBound()) {
        this->socket->OnConnected().Clear();
    }

    if (this->socket->OnConnectionError().IsBound()) {
        this->socket->OnConnectionError().Clear();
    }

    if (this->socket->OnClosed().IsBound()) {
        this->socket->OnClosed().Clear();
    }

    if (this->socket->OnMessage().IsBound()) {
        this->socket->OnMessage().Clear();
    }

    if (this->keepAliveTimerHandler.IsValid()) {
        this->gameInstance->GetTimerManager().ClearTimer(this->keepAliveTimerHandler);
        this->keepAliveTimerHandler.Invalidate();
    }
}

bool USubscriptionHandler::IsConnected () {
    return this->socket.IsValid() && this->socket->IsConnected();
}

void UCustomProtocolSubscriptionHandler::handleMessage(TSharedPtr<FJsonObject> JsonObject) {
    if (JsonObject->HasTypedField<EJson::String>("type")) {
        FString messageType = JsonObject->GetStringField("type");
        FString id;
        FString payload;
        if (JsonObject->HasTypedField<EJson::String>("id")) {
            id = JsonObject->GetStringField("id");
        }
        if (JsonObject->HasTypedField<EJson::Object>("payload")) {
            TSharedPtr<FJsonObject> dataPayload = JsonObject->GetObjectField("payload");
            payload = JsonObject->GetStringField("payload");

            TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&payload);
            FJsonSerializer::Serialize(dataPayload.ToSharedRef(), Writer);
        } else if (JsonObject->HasTypedField<EJson::Array>("payload")) {
            TArray < TSharedPtr < FJsonValue > > dataPayload = JsonObject->GetArrayField("payload");

            TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&payload);
            FJsonSerializer::Serialize(dataPayload, Writer);
        }

        this->OnReceiveAnyMessage(messageType, id, payload);
    } else {
        LOG_GRAPHQL_WARNING("no type field in message.");
    }
}

void UCustomProtocolSubscriptionHandler::OnConnected_Implementation() {
    this->connectAction->Complete(true, "");
}

void UCustomProtocolSubscriptionHandler::OnConnectionError_Implementation(const FString& errors) {
    this->connectAction->Complete(false, errors);
}

void UCustomProtocolSubscriptionHandler::OnClosed_Implementation(int32 StatusCode, const FString& Reason, bool bWasClean) {
}

bool UCustomProtocolSubscriptionHandler::sendStartSubscriptionRequest(
        FString customType,
        FString id,
        FString query,
        FString variables,
        TMap<FString, FString> authorization
) {
    if (this->socket.IsValid() && this->socket->IsConnected()) {
        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        JsonObject->SetStringField("type", customType);
        JsonObject->SetStringField("id", id);

        TSharedPtr<FJsonObject> payloadJsonObject = MakeShareable(new FJsonObject());

        {
            TSharedPtr<FJsonObject> dataJsonObject = MakeShareable(new FJsonObject());
            dataJsonObject->SetStringField("query", query);
            if (!variables.IsEmpty()) {
                TSharedPtr<FJsonObject> variablesJsonObject;
                TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(variables);
                if (FJsonSerializer::Deserialize(Reader, variablesJsonObject)) {
                    dataJsonObject->SetObjectField("variables", variablesJsonObject);
                } else {
                    LOG_GRAPHQL_WARNING("variables cannot be deserialized.");
                }
            } else {
                variables = FString("{}");
                TSharedPtr<FJsonObject> variablesJsonObject;
                TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(variables);
                if (FJsonSerializer::Deserialize(Reader, variablesJsonObject)) {
                    dataJsonObject->SetObjectField("variables", variablesJsonObject);
                } else {
                    LOG_GRAPHQL_WARNING("\"{}\" cannot be deserialized.");
                }
            }

            FString data;
            TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&data);
            FJsonSerializer::Serialize(dataJsonObject.ToSharedRef(), Writer);

            payloadJsonObject->SetStringField("data", data);
        }

        {
            TSharedPtr<FJsonObject> extensionsJsonObject = MakeShareable(new FJsonObject());

            {
                TSharedPtr<FJsonObject> authorizationJsonObject = MakeShareable(new FJsonObject());
                for (const TPair<FString, FString>& elem : authorization) {
                    authorizationJsonObject->SetStringField(elem.Key, elem.Value);
                }

                extensionsJsonObject->SetObjectField("authorization", authorizationJsonObject);
            }

            payloadJsonObject->SetObjectField("extensions", extensionsJsonObject);
        }

        JsonObject->SetObjectField("payload", payloadJsonObject);
        FString data;
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&data);
        FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
        socket->Send(data);
        return true;
    } else {
        LOG_GRAPHQL_WARNING("Subscribe GraphQL Subscription is not called or socket is not connected");
        return false;
    }
}

bool UCustomProtocolSubscriptionHandler::sendStopSubscriptionRequest(
        FString customType,
        FString id
) {
    if (this->socket.IsValid() && this->socket->IsConnected()) {
        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        JsonObject->SetStringField("type", customType);
        JsonObject->SetStringField("id", id);
        FString data;
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&data);
        FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
        socket->Send(data);
        return true;
    } else {
        LOG_GRAPHQL_WARNING("Subscribe GraphQL Subscription is not called or socket is not connected");
        return false;
    }
}

bool UCustomProtocolSubscriptionHandler::sendCustomMessage(
        FString customType,
        FString id,
        FString payload
) {
    if (this->socket.IsValid() && this->socket->IsConnected()) {
        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        JsonObject->SetStringField("type", customType);
        JsonObject->SetStringField("id", id);
        TSharedPtr<FJsonObject> payloadJsonObject;
        TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(payload);
        if (FJsonSerializer::Deserialize(Reader, payloadJsonObject)) {
            JsonObject->SetObjectField("payload", payloadJsonObject);
        } else {
            LOG_GRAPHQL_WARNING("payload cannot be deserialized. payload: " + payload);
        }

        FString data;
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&data);
        FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
        socket->Send(data);
        return true;
    } else {
        LOG_GRAPHQL_WARNING("Subscribe GraphQL Subscription is not called or socket is not connected");
        return false;
    }
}

void UCustomProtocolSubscriptionHandler::OnReceiveAnyMessage_Implementation(const FString& type, const FString& id, const FString& payload) {
}

void UCustomProtocolSubscriptionHandler::connect(
        UObject *WorldContextObject,
        bool &success,
        FString &errors,
        struct FLatentActionInfo LatentInfo
) {
    if (this->socket->OnConnected().IsBound()) {
        this->socket->OnConnected().Clear();
    }

    if (this->socket->OnConnectionError().IsBound()) {
        this->socket->OnConnectionError().Clear();
    }

    if (this->socket->OnClosed().IsBound()) {
        this->socket->OnClosed().Clear();
    }

    if (this->socket->OnMessage().IsBound()) {
        this->socket->OnMessage().Clear();
    }

    this->socket->OnConnected().AddLambda([this]() {
        this->OnConnected();
    });

    this->socket->OnConnectionError().AddLambda([this](const FString& error) {
        this->OnConnectionError(error);
    });

    this->socket->OnClosed().AddLambda([this](int32 StatusCode, const FString& Reason, bool bWasClean) {
        this->OnClosed(StatusCode, Reason, bWasClean);
    });

    this->socket->OnMessage().AddLambda([this](const FString& message) {
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(message);
        if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
            messageFailedToDeserialize = FString("");
            this->handleMessage(JsonObject);
        } else {
            LOG_GRAPHQL_WARNING("message cannot be deserialized. message: " + message);
            messageFailedToDeserialize = messageFailedToDeserialize
                    .Append(message);
            LOG_GRAPHQL_NORMAL("try again with combined message: " + message);
            Reader = TJsonReaderFactory<>::Create(messageFailedToDeserialize);
            if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
                messageFailedToDeserialize = FString("");
                this->handleMessage(JsonObject);
            }
        }
    });

    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FConnectAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            this->connectAction = new FConnectAction(
                    this->socket,
                    success,
                    errors,
                    LatentInfo
            );

            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, this->connectAction);
        }
    }
}

void UCustomProtocolSubscriptionHandler::disconnect(int32 Code, const FString& Reason) {
    this->socket->Close(Code, Reason);

    if (this->socket->OnConnected().IsBound()) {
        this->socket->OnConnected().Clear();
    }

    if (this->socket->OnConnectionError().IsBound()) {
        this->socket->OnConnectionError().Clear();
    }

    if (this->socket->OnClosed().IsBound()) {
        this->socket->OnClosed().Clear();
    }

    if (this->socket->OnMessage().IsBound()) {
        this->socket->OnMessage().Clear();
    }
}

bool UCustomProtocolSubscriptionHandler::IsConnected () {
    return this->socket.IsValid() && this->socket->IsConnected();
}

class FSendGraphQLRequestAction : public FPendingLatentAction {
private:
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request;

	bool &success;
	int32 &responseCode;
	FString &data;
	FString &extensions;
	FString &errors;

    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

public:
    FSendGraphQLRequestAction(
        bool &success,
        FString endpoint,
        EGraphQLHttpMethod method,
        FString query,
        FString operationName,
        FString variables,
        TMap<FString, FString> headers,
        int32 &responseCode,
        FString &data,
        FString &extensions,
        FString &errors,
        const FLatentActionInfo &LatentInfo
    ) :
	Request(FHttpModule::Get().CreateRequest()),
	success(success),
	responseCode(responseCode),
	data(data),
	extensions(extensions),
	errors(errors),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {
        switch (method) {
            case EGraphQLHttpMethod::POST:
            {
                Request->SetVerb("POST");
                Request->SetURL(endpoint);

                TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
                JsonObject->SetStringField("query", query);
                if (!operationName.IsEmpty()) {
                    JsonObject->SetStringField("operationName", operationName);
                }
                if (!variables.IsEmpty()) {
                    TSharedPtr<FJsonObject> variablesJsonObject;
                    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(variables);
                    if (FJsonSerializer::Deserialize(Reader, variablesJsonObject)) {
                        JsonObject->SetObjectField("variables", variablesJsonObject);
                    } else {
                        LOG_GRAPHQL_WARNING("variables cannot be deserialized.");
                    }
                }
                FString contentString;
                TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&contentString);
                if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer)) {
                    LOG_GRAPHQL_NORMAL("Send GraphQL POST Request, conntent string: " + contentString);
                    Request->SetContentAsString(contentString);
                }
            }

                break;
            case EGraphQLHttpMethod::GET:
            {
                Request->SetVerb("GET");
                FString url = endpoint + "?" + "query=" + query;
                if (!operationName.IsEmpty()) {
                    url.Append("&operationName=" + operationName);
                }
                if (!variables.IsEmpty()) {
                    url.Append("&variables=" + variables);
                }
                Request->SetURL(url);
                LOG_GRAPHQL_NORMAL("Send GraphQL GET Request, Calculated url: " + url);
            }

                break;
            default:
            {
                Request->SetVerb("POST");
                Request->SetURL(endpoint);

                TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
                JsonObject->SetStringField("query", query);
                if (!operationName.IsEmpty()) {
                    JsonObject->SetStringField("operationName", operationName);
                }
                if (!variables.IsEmpty()) {
                    TSharedPtr<FJsonObject> variablesJsonObject;
                    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(variables);
                    if (FJsonSerializer::Deserialize(Reader, variablesJsonObject)) {
                        JsonObject->SetObjectField("variables", variablesJsonObject);
                    } else {
                        LOG_GRAPHQL_WARNING("variables cannot be deserialized.");
                    }
                }
                FString contentString;
                TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&contentString);
                if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer)) {
                    LOG_GRAPHQL_NORMAL("Send GraphQL POST Request, conntent string: " + contentString);
                    Request->SetContentAsString(contentString);
                }
            }

                break;
        }
        for (const TPair<FString, FString>& elem : headers) {
            Request->SetHeader(elem.Key, elem.Value);
        }
        Request->ProcessRequest();
    }

    void UpdateOperation(FLatentResponse &Response) override {
	    EHttpRequestStatus::Type status = Request->GetStatus();

	    if (status == EHttpRequestStatus::Type::NotStarted) {
		    LOG_GRAPHQL_WARNING("Send GraphQL Request is not started...");
		    Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
		    return;
	    }

	    if (status == EHttpRequestStatus::Type::Processing) {
		    Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
		    return;
	    }

	    if (status == EHttpRequestStatus::Type::Failed) {
		    success = false;
		    LOG_GRAPHQL_WARNING("Send GraphQL Request failed...");
		    Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		    return;
	    }

	    if (status == EHttpRequestStatus::Type::Failed_ConnectionError) {
		    success = false;
		    LOG_GRAPHQL_WARNING("connection failed...Please check url and retry later.");
		    Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		    return;
	    }

	    if (status == EHttpRequestStatus::Type::Succeeded) {
		    FHttpResponsePtr httpResponse = Request->GetResponse();
		    success = true;

		    TSharedPtr<FJsonObject> JsonObject;
		    TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(httpResponse->GetContentAsString());
		    if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
			    if (JsonObject->HasTypedField<EJson::Array>("errors")) {
				    TArray < TSharedPtr < FJsonValue > > errorsJsonArray = JsonObject->GetArrayField("errors");

				    TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&errors);
				    FJsonSerializer::Serialize(errorsJsonArray, Writer);
			    }

			    if (JsonObject->HasTypedField<EJson::Object>("extensions")) {
				    TSharedPtr<FJsonObject> extensionsJsonObject = JsonObject->GetObjectField("extensions");

				    TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&extensions);
				    FJsonSerializer::Serialize(extensionsJsonObject.ToSharedRef(), Writer);
			    }

			    if (JsonObject->HasTypedField<EJson::Object>("data")) {
				    TSharedPtr<FJsonObject> dataJsonObject = JsonObject->GetObjectField("data");

				    TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&data);
				    FJsonSerializer::Serialize(dataJsonObject.ToSharedRef(), Writer);
			    } else {
				    LOG_GRAPHQL_WARNING("no data field in response.");
			    }
		    } else {
			    LOG_GRAPHQL_WARNING("response cannot be deserialized.");
		    }

		    responseCode = httpResponse->GetResponseCode();

		    Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		    return;
	    }

	    LOG_GRAPHQL_WARNING("Send GraphQL Request unknown status...");
	    Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("Send GraphQL Request");
    }

#endif
};

void
UGraphQLFunctionLibrary::SendGraphQLRequest (
        UObject *WorldContextObject,
        bool &success,
        FString endpoint,
        EGraphQLHttpMethod method,
        FString query,
        FString operationName,
        FString variables,
        TMap<FString, FString> headers,
        int32 &responseCode,
        FString &data,
        FString &extensions,
        FString &errors,
        struct FLatentActionInfo LatentInfo
) {
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FSendGraphQLRequestAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FSendGraphQLRequestAction(
                    success,
                    endpoint,
                    method,
                    query,
                    operationName,
                    variables,
                    headers,
                    responseCode,
                    data,
                    extensions,
                    errors,
                    LatentInfo
                )
            );
        }
    }
    return;
}

void
UGraphQLFunctionLibrary::SubscribeGraphQLSubscription (
        FString endpoint,
        TMap<FString, FString> headers,
        TMap<FString, FString> queryParameters,
        USubscriptionHandler *handler
) {
#if WITH_WEBSOCKETS
    // Prepare latent action
    FString url = endpoint;
    if (queryParameters.Num() > 0) {
        url = url.Append("?");
        for (const TPair<FString, FString> &queryParameter : queryParameters) {
            url = url
                    .Append(queryParameter.Key)
                    .Append("=")
                    .Append(FGenericPlatformHttp::UrlEncode(queryParameter.Value))
                    .Append("&");
        }
        url.RemoveFromEnd("&", ESearchCase::Type::CaseSensitive);
    }
    LOG_GRAPHQL_NORMAL("graphql realtime url: " + url);
    handler->socket = TSharedPtr < IWebSocket >(FWebSocketsModule::Get().CreateWebSocket(url, FString("graphql-ws"), headers));
#endif
}

void
UGraphQLFunctionLibrary::SubscribeGraphQLCustomProtocolSubscription (
        FString endpoint,
        TMap<FString, FString> headers,
        TMap<FString, FString> queryParameters,
        FString customProtocol,
        UCustomProtocolSubscriptionHandler *handler
) {
#if WITH_WEBSOCKETS
    // Prepare latent action
    FString url = endpoint;
    if (queryParameters.Num() > 0) {
        url = url.Append("?");
        for (const TPair<FString, FString> &queryParameter : queryParameters) {
            url = url
                    .Append(queryParameter.Key)
                    .Append("=")
                    .Append(FGenericPlatformHttp::UrlEncode(queryParameter.Value))
                    .Append("&");
        }
        url.RemoveFromEnd("&", ESearchCase::Type::CaseSensitive);
    }
    LOG_GRAPHQL_NORMAL("graphql realtime url: " + url);
    handler->socket = TSharedPtr < IWebSocket >(FWebSocketsModule::Get().CreateWebSocket(url, customProtocol, headers));
#endif
}

void
UGraphQLFunctionLibrary::AWSAppSyncGraphQLApiKeyHelper (
        FString host,
        FString apiKey,
        TMap<FString, FString> &Headers,
        TMap<FString, FString> &QueryParameters,
        TMap<FString, FString> &Authorization
) {
    {
        Headers.Add("Content-Type", "application/graphql");
        Headers.Add("x-api-key", apiKey);
    }
    
    {
        QueryParameters.Add("payload", FBase64::Encode(FString("{}")));

        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        JsonObject->SetStringField("host", host);
        JsonObject->SetStringField("x-api-key", apiKey);
        FString headerContents;
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&headerContents);
        if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer)) {
            LOG_GRAPHQL_NORMAL("header data: " + headerContents);
            QueryParameters.Add("header", FBase64::Encode(headerContents));
        }
    }
    
    {
        Authorization.Add("host", host);
        Authorization.Add("x-api-key", apiKey);
    }
}

void
UGraphQLFunctionLibrary::AWSAppSyncGraphQLOIDCHelper (
        FString host,
        FString accessToken,
        TMap<FString, FString> &Headers,
        TMap<FString, FString> &QueryParameters,
        TMap<FString, FString> &Authorization
) {
    {
        Headers.Add("Content-Type", "application/graphql");
        Headers.Add("Authorization", accessToken);
    }
    
    {
        QueryParameters.Add("payload", FBase64::Encode(FString("{}")));

        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        JsonObject->SetStringField("host", host);
        JsonObject->SetStringField("Authorization", accessToken);
        FString headerContents;
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&headerContents);
        if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer)) {
            LOG_GRAPHQL_NORMAL("header data: " + headerContents);
            QueryParameters.Add("header", FBase64::Encode(headerContents));
        }
    }
    
    {
        Authorization.Add("host", host);
        Authorization.Add("Authorization", accessToken);
    }
}

void
UGraphQLFunctionLibrary::AWSAppSyncGraphQLIAMHelper (
        FString host,
        FString accessKeyId,
        FString secretKey,
        FString securityToken,
        FString query,
        FString operationName,
        FString variables,
        FDateTime date,
        TMap<FString, FString> &Headers,
        TMap<FString, FString> &QueryParameters,
        TMap<FString, FString> &Authorization,
        FString region,
        FString service,
        FString algorithm,
        FString accept,
        FString contentEncoding,
        FString contentType
) {
    {
        Headers.Add("host", host);
        Headers.Add("accept", accept);
        Headers.Add("content-encoding", contentEncoding);
        Headers.Add("content-type", contentType);
        Headers.Add("x-amz-date", date.ToString(TEXT("%Y%m%dT%H%M%SZ")));
        if (!(securityToken.IsEmpty())) {
            Headers.Add("X-Amz-Security-Token", securityToken);
        }

        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        JsonObject->SetStringField("query", query);
        if (!operationName.IsEmpty()) {
            JsonObject->SetStringField("operationName", operationName);
        }
        if (!variables.IsEmpty()) {
            TSharedPtr<FJsonObject> variablesJsonObject;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(variables);
            if (FJsonSerializer::Deserialize(Reader, variablesJsonObject)) {
                JsonObject->SetObjectField("variables", variablesJsonObject);
            } else {
                LOG_GRAPHQL_WARNING("variables cannot be deserialized.");
            }
        }
        FString contentString;
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&contentString);
        FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

        Headers.Add("Authorization", CalculateSigV4(host, FString("/graphql"), FString(""), contentString, accessKeyId, secretKey, securityToken, date, region, service, algorithm, accept, contentEncoding, contentType));
    }
    
    {
        QueryParameters.Add("payload", FBase64::Encode(FString("{}")));

        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        JsonObject->SetStringField("host", host);
        JsonObject->SetStringField("accept", accept);
        JsonObject->SetStringField("content-encoding", contentEncoding);
        JsonObject->SetStringField("content-type", contentType);
        JsonObject->SetStringField("x-amz-date", date.ToString(TEXT("%Y%m%dT%H%M%SZ")));
        if (!(securityToken.IsEmpty())) {
            JsonObject->SetStringField("X-Amz-Security-Token", securityToken);
        }

        JsonObject->SetStringField("Authorization", CalculateSigV4(host, FString("/graphql/connect"), FString(""), FString("{}"), accessKeyId, secretKey, securityToken, date, region, service, algorithm, accept, contentEncoding, contentType));
        FString headerContents;
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&headerContents);
        if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer)) {
            LOG_GRAPHQL_NORMAL("header data: " + headerContents);
            QueryParameters.Add("header", FBase64::Encode(headerContents));
        }
    }
    
    {
        Authorization.Add("host", host);
        Authorization.Add("accept", accept);
        Authorization.Add("content-encoding", contentEncoding);
        Authorization.Add("content-type", contentType);
        Authorization.Add("x-amz-date", date.ToString(TEXT("%Y%m%dT%H%M%SZ")));
        if (!(securityToken.IsEmpty())) {
            Authorization.Add("X-Amz-Security-Token", securityToken);
        }

        TSharedPtr<FJsonObject> dataJsonObject = MakeShareable(new FJsonObject());
        dataJsonObject->SetStringField("query", query);
        if (!variables.IsEmpty()) {
            TSharedPtr<FJsonObject> variablesJsonObject;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(variables);
            if (FJsonSerializer::Deserialize(Reader, variablesJsonObject)) {
                dataJsonObject->SetObjectField("variables", variablesJsonObject);
            } else {
                LOG_GRAPHQL_WARNING("variables cannot be deserialized.");
            }
        } else {
            variables = FString("{}");
            TSharedPtr<FJsonObject> variablesJsonObject;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(variables);
            if (FJsonSerializer::Deserialize(Reader, variablesJsonObject)) {
                dataJsonObject->SetObjectField("variables", variablesJsonObject);
            } else {
                LOG_GRAPHQL_WARNING("\"{}\" cannot be deserialized.");
            }
        }

        FString data;
        TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&data);
        FJsonSerializer::Serialize(dataJsonObject.ToSharedRef(), Writer);

        Authorization.Add("Authorization", CalculateSigV4(host, FString("/graphql"), FString(""), data, accessKeyId, secretKey, securityToken, date, region, service, algorithm, accept, contentEncoding, contentType));
    }
}

FString UGraphQLFunctionLibrary::CalculateSigV4 (
        FString host,
        FString canonicalURI,
        FString canonicalQueryString,
        FString payload,
        FString accessKeyId,
        FString secretKey,
        FString securityToken,
        FDateTime date,
        FString region,
        FString service,
        FString algorithm,
        FString accept,
        FString contentEncoding,
        FString contentType
) {
    TMap<FString, FString> canonicalheaders;
    canonicalheaders.Add("accept", accept);
    canonicalheaders.Add("content-encoding", contentEncoding);
    canonicalheaders.Add("content-type", contentType);
    canonicalheaders.Add("host", host);
    canonicalheaders.Add("x-amz-date", date.ToString(TEXT("%Y%m%dT%H%M%SZ")));
    if (!(securityToken.IsEmpty())) {
        canonicalheaders.Add("X-Amz-Security-Token", securityToken);
    }

    FString canonicalheadersString = FString("");
    FString signedHeaders = FString("");

    for (const TPair<FString, FString> &canonicalheader : canonicalheaders) {
        canonicalheadersString = canonicalheadersString
                .Append(canonicalheader.Key.ToLower())
                .Append(":")
                .Append(canonicalheader.Value)
                .Append("\n");
        signedHeaders = signedHeaders.Append(canonicalheader.Key.ToLower()).Append(";");
    }

    signedHeaders.RemoveFromEnd(";", ESearchCase::Type::CaseSensitive);

    LOG_GRAPHQL_NORMAL("payload: " + payload);
    FString hashedPayload;
    if (algorithm.Equals(FString("AWS4-HMAC-SHA256"), ESearchCase::Type::CaseSensitive)) {
        hashedPayload = GetSHA256HEXSignature(payload);
    }
    FString canonicalRequest = FString::Printf(TEXT("%s\n%s\n%s\n%s\n%s\n%s"), *FString("POST"), *canonicalURI, *canonicalQueryString, *canonicalheadersString, *signedHeaders, *hashedPayload);
    LOG_GRAPHQL_NORMAL("canonical request: " + canonicalRequest);
    FString hashedCanonicalRequest;
    if (algorithm.Equals(FString("AWS4-HMAC-SHA256"), ESearchCase::Type::CaseSensitive)) {
        hashedCanonicalRequest = GetSHA256HEXSignature(canonicalRequest);
    }
    FString credentialScope = FString::Printf(TEXT("%s/%s/%s/aws4_request"), *date.ToString(TEXT("%Y%m%d")), *region, *service);
    FString stringToSign = FString::Printf(TEXT("%s\n%s\n%s\n%s"), *algorithm, *date.ToString(TEXT("%Y%m%dT%H%M%SZ")), *credentialScope, *hashedCanonicalRequest);
    LOG_GRAPHQL_NORMAL("string to sign: " + stringToSign);
    FString signature;
    if (algorithm.Equals(FString("AWS4-HMAC-SHA256"), ESearchCase::Type::CaseSensitive)) {
        FString AWS4 = "AWS4" + secretKey;

        std::string Kdate = GetHMACSHA256Signature(TCHAR_TO_UTF8(*AWS4), TCHAR_TO_UTF8(*date.ToString(TEXT("%Y%m%d"))));
        LOG_GRAPHQL_NORMAL("date key: " + BytesToHex((const uint8 *)Kdate.c_str(), sizeof(Kdate)).ToLower());

        std::string Kregion = GetHMACSHA256Signature(Kdate, TCHAR_TO_UTF8(*region));
        LOG_GRAPHQL_NORMAL("region key: " + BytesToHex((const uint8 *)Kregion.c_str(), sizeof(Kregion)).ToLower());

        std::string Kservice = GetHMACSHA256Signature(Kregion, TCHAR_TO_UTF8(*service));
        LOG_GRAPHQL_NORMAL("service key: " + BytesToHex((const uint8 *)Kservice.c_str(), sizeof(Kservice)).ToLower());

        std::string kSigning = GetHMACSHA256Signature(Kservice, "aws4_request" );
        LOG_GRAPHQL_NORMAL("signing key: " + BytesToHex((const uint8 *)kSigning.c_str(), sizeof(kSigning)).ToLower());

        signature = GetHMACSHA256HEXSignature(kSigning, TCHAR_TO_UTF8(*stringToSign));
        LOG_GRAPHQL_NORMAL("signature: " + signature);
    }
    FString authorization = FString::Printf(TEXT("%s Credential=%s/%s, SignedHeaders=%s, Signature=%s"), *algorithm, *accessKeyId, *credentialScope, *signedHeaders, *signature);
    
    return authorization;
}
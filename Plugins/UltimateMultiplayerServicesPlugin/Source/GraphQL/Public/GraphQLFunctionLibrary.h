/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, October 2020
 */

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/LatentActionManager.h"
#include "IWebSocket.h"
#include "Misc/DateTime.h"
#include "Engine/EngineTypes.h"
#include "Dom/JsonObject.h"
#include "Engine/GameInstance.h"

#include "GraphQLFunctionLibrary.generated.h"

UENUM(BlueprintType)
enum class EGraphQLHttpMethod : uint8 {
    POST      UMETA(DisplayName = "post"),
    GET      UMETA(DisplayName = "get")
};

class FConnectAction;
class FSendStartSubscriptionRequestAction;
class FSendStopSubscriptionRequestAction;

UCLASS(Blueprintable)
class GRAPHQL_API USubscriptionHandler : public UObject {
    GENERATED_BODY()
    
    FTimerHandle keepAliveTimerHandler = FTimerHandle();
    bool keepAlive;
    
    FString messageFailedToDeserialize = FString("");
    
    void handleMessage(TSharedPtr<FJsonObject> JsonObject);

public:
    TSharedPtr < IWebSocket > socket;
    FConnectAction * connectAction;
    TMap<FString, FSendStartSubscriptionRequestAction *> sendStartSubscriptionRequestActions;
    TMap<FString, FSendStopSubscriptionRequestAction *> sendStopSubscriptionRequestActions;

    /**
     * use to setup timer
     * */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GraphQL Function", Meta = (ExposeOnSpawn = true))
    UGameInstance *gameInstance;

    UFUNCTION(BlueprintNativeEvent, Category = "GraphQL Function")
    void OnGraphQLError(const FString& id, const FString& errors);

    UFUNCTION(BlueprintNativeEvent, Category = "GraphQL Function")
    void OnGraphQLConnectionError(const FString& errors);

    UFUNCTION(BlueprintNativeEvent, Category = "GraphQL Function")
    void OnConnected();

    UFUNCTION(BlueprintNativeEvent, Category = "GraphQL Function")
    void OnConnectionError(const FString& errors);

    UFUNCTION(BlueprintNativeEvent, Category = "GraphQL Function")
    void OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean);

    UFUNCTION(BlueprintNativeEvent, Category = "GraphQL Function")
    void OnKeepAliveMessageMissed();

    UFUNCTION(BlueprintNativeEvent, Category = "GraphQL Function")
    void OnReceiveStartACKMessage(const FString& id);

    UFUNCTION(BlueprintNativeEvent, Category = "GraphQL Function")
    void OnReceiveCompleteMessage(const FString& id);

    UFUNCTION(BlueprintNativeEvent, Category = "GraphQL Function")
    void OnReceiveDataMessage(const FString& id, const FString& data);

//    UFUNCTION(BlueprintCallable, Category = "GraphQL Function")
    bool sendConnectionInitRequest ();

    UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "GraphQL Function")
    bool sendStartSubscriptionRequest (
        UObject *WorldContextObject,
        bool &success,
        FString id,
        FString query,
        FString variables,
        TMap<FString, FString> authorization,
        FString &errors,
        struct FLatentActionInfo LatentInfo
    );

    UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "GraphQL Function")
    bool sendStopSubscriptionRequest (
        UObject *WorldContextObject,
        bool &success,
        FString id,
        FString &errors,
        struct FLatentActionInfo LatentInfo
    );

    UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "GraphQL Function")
    void connect (
            UObject *WorldContextObject,
            bool &success,
            FString &errors,
            struct FLatentActionInfo LatentInfo
    );

    UFUNCTION(BlueprintCallable, Category = "GraphQL Function")
    void disconnect (int32 Code = 1000, const FString& Reason = FString(""));

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GraphQL Function")
    bool IsConnected ();

	virtual void BeginDestroy() override {
		Super::BeginDestroy();
		if (this->IsConnected()) {
			this->disconnect();
		}
	}
    
    ~USubscriptionHandler() {
        this->gameInstance = nullptr;
    };
};

UCLASS(Blueprintable)
class GRAPHQL_API UCustomProtocolSubscriptionHandler : public UObject {
    GENERATED_BODY()

    FString messageFailedToDeserialize = FString("");

    void handleMessage(TSharedPtr<FJsonObject> JsonObject);

public:
    TSharedPtr < IWebSocket > socket;
    FConnectAction * connectAction;

    UFUNCTION(BlueprintNativeEvent, Category = "GraphQL Function")
    void OnConnected();

    UFUNCTION(BlueprintNativeEvent, Category = "GraphQL Function")
    void OnConnectionError(const FString& errors);

    UFUNCTION(BlueprintNativeEvent, Category = "GraphQL Function")
    void OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean);

    UFUNCTION(BlueprintCallable, Category = "GraphQL Function")
    bool sendStartSubscriptionRequest (
            FString customType,
            FString id,
            FString query,
            FString variables,
            TMap<FString, FString> authorization
    );

    UFUNCTION(BlueprintCallable, Category = "GraphQL Function")
    bool sendStopSubscriptionRequest (
            FString customType,
            FString id
    );

    UFUNCTION(BlueprintCallable, Category = "GraphQL Function")
    bool sendCustomMessage (
            FString customType,
            FString id,
            FString payload
    );

    UFUNCTION(BlueprintNativeEvent, Category = "GraphQL Function")
    void OnReceiveAnyMessage(const FString& type, const FString& id, const FString& payload);

    UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "GraphQL Function")
    void connect (
            UObject *WorldContextObject,
            bool &success,
            FString &errors,
    struct FLatentActionInfo LatentInfo
);

    UFUNCTION(BlueprintCallable, Category = "GraphQL Function")
    void disconnect (int32 Code = 1000, const FString& Reason = FString(""));

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GraphQL Function")
    bool IsConnected ();

	virtual void BeginDestroy() override {
		Super::BeginDestroy();
		if (this->IsConnected()) {
			this->disconnect();
		}
	}

    ~UCustomProtocolSubscriptionHandler() {
    };
};

/**
 * 
 */
UCLASS()
class GRAPHQL_API UGraphQLFunctionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

public:
    /**
     *
    */
    UFUNCTION(BlueprintCallable, meta = (Latent, LatentInfo = "LatentInfo", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "GraphQL Function")
    static void SendGraphQLRequest (
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
    );

    /**
     * @param endpoint: the graphql real-time endpoint
    */
    UFUNCTION(BlueprintCallable, Category = "GraphQL Function")
    static void SubscribeGraphQLSubscription (
        FString endpoint,
        TMap<FString, FString> headers,
        TMap<FString, FString> queryParameters,
        USubscriptionHandler *handler
    );

    /**
     * @param endpoint: the graphql real-time endpoint
     * @param customProtocol: for apollo server 3.5.10 or later, subprotocol is graphql-transport-ws; for apollo server earlier than 3.5.10, subprotocol is graphql-ws
    */
    UFUNCTION(BlueprintCallable, Category = "GraphQL Function")
    static void SubscribeGraphQLCustomProtocolSubscription (
        FString endpoint,
        TMap<FString, FString> headers,
        TMap<FString, FString> queryParameters,
        FString customProtocol,
        UCustomProtocolSubscriptionHandler *handler
    );

    /**
     *
    */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GraphQL Function")
    static void AWSAppSyncGraphQLApiKeyHelper (
            FString host,
            FString apiKey,
            TMap<FString, FString> &Headers,
            TMap<FString, FString> &QueryParameters,
            TMap<FString, FString> &Authorization
    );

    /**
     * @param accessToken: use Amazon Cognito user pools and OpenID Connect as authorization mode. JWT Access Token.
     * if you are using aws cognito user pool, you don't need to add "Bearer" in front of access token.
    */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GraphQL Function")
    static void AWSAppSyncGraphQLOIDCHelper (
            FString host,
            FString accessToken,
            TMap<FString, FString> &Headers,
            TMap<FString, FString> &QueryParameters,
            TMap<FString, FString> &Authorization
    );

    /**
     * @param query: use IAM as authorization mode. the graphql query
     * @param operationName: use IAM as authorization mode. the graphql operationName
     * @param variables: use IAM as authorization mode. the graphql variables
     * @param date: use IAM as authorization mode. Utc Now
     * @param securityToken: use IAM as authorization mode. The AWS session token, which is required when using temporary security credentials. For more information, see Using Temporary Credentials With AWS Resources in the IAM User Guide.
     * @param authorization: use IAM as authorization mode. SigV4 signing information for the AWS AppSync endpoint. For more information on the signing process, see Task 4: Add the signature to the HTTP request in the AWS General Reference.
    */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GraphQL Function")
    static void AWSAppSyncGraphQLIAMHelper (
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
            FString region = FString("us-east-1"),
            FString service = FString("appsync"),
            FString algorithm = FString("AWS4-HMAC-SHA256"),
            FString accept = FString("application/json, text/javascript"),
            FString contentEncoding = FString("amz-1.0"),
            FString contentType = FString("application/json; charset=UTF-8")
    );

    /**
     * @param host: This is the host for the AWS AppSync GraphQL endpoint.
     * @param date: use IAM as authorization mode. Utc Now
     * @param securityToken: use IAM as authorization mode. The AWS session token, which is required when using temporary security credentials. For more information, see Using Temporary Credentials With AWS Resources in the IAM User Guide.
     * @param authorization: use IAM as authorization mode. SigV4 signing information for the AWS AppSync endpoint. For more information on the signing process, see Task 4: Add the signature to the HTTP request in the AWS General Reference.
    */
    UFUNCTION(BlueprintCallable, Category = "GraphQL Function")
    static FString CalculateSigV4 (
            FString host,
            FString canonicalURI,
            FString canonicalQueryString,
            FString payload,
            FString accessKeyId,
            FString secretKey,
            FString securityToken,
            FDateTime date,
            FString region = FString("us-east-1"),
            FString service = FString("appsync"),
            FString algorithm = FString("AWS4-HMAC-SHA256"),
            FString accept = FString("application/json, text/javascript"),
            FString contentEncoding = FString("amz-1.0"),
            FString contentType = FString("application/json; charset=UTF-8")
    );
};

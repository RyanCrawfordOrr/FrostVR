/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#include "CloudWatchLogsClientObject.h"
#include "CloudWatchLogsGlobals.h"
#include "CloudWatchLogsPrivatePCH.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "Runtime/Engine/Classes/Engine/Engine.h"

#include "LatentActions.h"

#include "aws/core/utils/Outcome.h"
#include "aws/core/client/AWSError.h"

#endif

#if WITH_CLOUDWATCHLOGSCLIENTSDK

ECloudWatchLogsError fromAWS(Aws::CloudWatchLogs::CloudWatchLogsErrors awsErrorType) {
    switch (awsErrorType) {
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::INCOMPLETE_SIGNATURE:
            return ECloudWatchLogsError::INCOMPLETE_SIGNATURE;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::INTERNAL_FAILURE:
            return ECloudWatchLogsError::INTERNAL_FAILURE;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::INVALID_ACTION:
            return ECloudWatchLogsError::INVALID_ACTION;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::INVALID_CLIENT_TOKEN_ID:
            return ECloudWatchLogsError::INVALID_CLIENT_TOKEN_ID;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::INVALID_PARAMETER_COMBINATION:
            return ECloudWatchLogsError::INVALID_PARAMETER_COMBINATION;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::INVALID_QUERY_PARAMETER:
            return ECloudWatchLogsError::INVALID_QUERY_PARAMETER;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::INVALID_PARAMETER_VALUE:
            return ECloudWatchLogsError::INVALID_PARAMETER_VALUE;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::MISSING_ACTION:
            return ECloudWatchLogsError::MISSING_ACTION;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::MISSING_AUTHENTICATION_TOKEN:
            return ECloudWatchLogsError::MISSING_AUTHENTICATION_TOKEN;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::MISSING_PARAMETER:
            return ECloudWatchLogsError::MISSING_PARAMETER;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::OPT_IN_REQUIRED:
            return ECloudWatchLogsError::OPT_IN_REQUIRED;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::REQUEST_EXPIRED:
            return ECloudWatchLogsError::REQUEST_EXPIRED;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::SERVICE_UNAVAILABLE:
            return ECloudWatchLogsError::SERVICE_UNAVAILABLE;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::THROTTLING:
            return ECloudWatchLogsError::THROTTLING;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::VALIDATION:
            return ECloudWatchLogsError::VALIDATION;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::ACCESS_DENIED:
            return ECloudWatchLogsError::ACCESS_DENIED;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::RESOURCE_NOT_FOUND:
            return ECloudWatchLogsError::RESOURCE_NOT_FOUND;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::UNRECOGNIZED_CLIENT:
            return ECloudWatchLogsError::UNRECOGNIZED_CLIENT;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::MALFORMED_QUERY_STRING:
            return ECloudWatchLogsError::MALFORMED_QUERY_STRING;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::SLOW_DOWN:
            return ECloudWatchLogsError::SLOW_DOWN;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::REQUEST_TIME_TOO_SKEWED:
            return ECloudWatchLogsError::REQUEST_TIME_TOO_SKEWED;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::INVALID_SIGNATURE:
            return ECloudWatchLogsError::INVALID_SIGNATURE;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::SIGNATURE_DOES_NOT_MATCH:
            return ECloudWatchLogsError::SIGNATURE_DOES_NOT_MATCH;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::INVALID_ACCESS_KEY_ID:
            return ECloudWatchLogsError::INVALID_ACCESS_KEY_ID;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::REQUEST_TIMEOUT:
            return ECloudWatchLogsError::REQUEST_TIMEOUT;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::NETWORK_CONNECTION:
            return ECloudWatchLogsError::NETWORK_CONNECTION;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::UNKNOWN:
            return ECloudWatchLogsError::UNKNOWN;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::DATA_ALREADY_ACCEPTED:
            return ECloudWatchLogsError::DATA_ALREADY_ACCEPTED;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::INVALID_OPERATION:
            return ECloudWatchLogsError::INVALID_OPERATION;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::INVALID_PARAMETER:
            return ECloudWatchLogsError::INVALID_PARAMETER;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::INVALID_SEQUENCE_TOKEN:
            return ECloudWatchLogsError::INVALID_SEQUENCE_TOKEN;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::LIMIT_EXCEEDED:
            return ECloudWatchLogsError::LIMIT_EXCEEDED;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::MALFORMED_QUERY:
            return ECloudWatchLogsError::MALFORMED_QUERY;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::OPERATION_ABORTED:
            return ECloudWatchLogsError::OPERATION_ABORTED;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::RESOURCE_ALREADY_EXISTS:
            return ECloudWatchLogsError::RESOURCE_ALREADY_EXISTS;
            break;
        case Aws::CloudWatchLogs::CloudWatchLogsErrors::TOO_MANY_TAGS:
            return ECloudWatchLogsError::TOO_MANY_TAGS;
            break;
        default:
            return ECloudWatchLogsError::UNKNOWN;
            break;
    }
}

#endif

UCloudWatchLogsClientObject *UCloudWatchLogsClientObject::CreateCloudWatchLogsObject(
    const FAWSCredentials &credentials,
    const FAWSClientConfiguration &clientConfiguration
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    UCloudWatchLogsClientObject *LogsClient = NewObject<UCloudWatchLogsClientObject>();
    LogsClient->awsCloudWatchLogsClient = new Aws::CloudWatchLogs::CloudWatchLogsClient(credentials.toAWS(),
    Aws::MakeShared<Aws::CloudWatchLogs::CloudWatchLogsEndpointProvider>("unreal"),
    clientConfiguration.toAWS());
    return LogsClient;
#endif
    return nullptr;
}

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FAssociateKmsKeyAction : public FPendingLatentAction {
private:
    bool &success;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::AssociateKmsKeyOutcomeCallable callable;

public:
    FAssociateKmsKeyAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FAssociateKmsKeyRequest associateKmsKeyRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->AssociateKmsKeyCallable(associateKmsKeyRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsAssociateKmsKeyOutcome = callable.get();

            success = awsAssociateKmsKeyOutcome.IsSuccess();

                errorType = fromAWS(awsAssociateKmsKeyOutcome.GetError().GetErrorType());
                errorMessage = ("AssociateKmsKey error: " + awsAssociateKmsKeyOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("AssociateKmsKey Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::AssociateKmsKey(
    UObject *WorldContextObject,
    bool &success,
    FAssociateKmsKeyRequest associateKmsKeyRequest,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FAssociateKmsKeyAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FAssociateKmsKeyAction(this->awsCloudWatchLogsClient,
                success,
                associateKmsKeyRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FCancelExportTaskAction : public FPendingLatentAction {
private:
    bool &success;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::CancelExportTaskOutcomeCallable callable;

public:
    FCancelExportTaskAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FCancelExportTaskRequest cancelExportTaskRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->CancelExportTaskCallable(cancelExportTaskRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsCancelExportTaskOutcome = callable.get();

            success = awsCancelExportTaskOutcome.IsSuccess();

                errorType = fromAWS(awsCancelExportTaskOutcome.GetError().GetErrorType());
                errorMessage = ("CancelExportTask error: " + awsCancelExportTaskOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("CancelExportTask Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::CancelExportTask(
    UObject *WorldContextObject,
    bool &success,
    FCancelExportTaskRequest cancelExportTaskRequest,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FCancelExportTaskAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FCancelExportTaskAction(this->awsCloudWatchLogsClient,
                success,
                cancelExportTaskRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FCreateExportTaskAction : public FPendingLatentAction {
private:
    bool &success;
    FCreateExportTaskResult &createExportTaskResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::CreateExportTaskOutcomeCallable callable;

public:
    FCreateExportTaskAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FCreateExportTaskRequest createExportTaskRequest,
        FCreateExportTaskResult &createExportTaskResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), createExportTaskResult(createExportTaskResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->CreateExportTaskCallable(createExportTaskRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsCreateExportTaskOutcome = callable.get();

            success = awsCreateExportTaskOutcome.IsSuccess();
                if (success) {
                    createExportTaskResult.fromAWS(awsCreateExportTaskOutcome.GetResult());
                }

                errorType = fromAWS(awsCreateExportTaskOutcome.GetError().GetErrorType());
                errorMessage = ("CreateExportTask error: " + awsCreateExportTaskOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("CreateExportTask Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::CreateExportTask(
    UObject *WorldContextObject,
    bool &success,
    FCreateExportTaskRequest createExportTaskRequest,
    FCreateExportTaskResult &createExportTaskResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FCreateExportTaskAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FCreateExportTaskAction(this->awsCloudWatchLogsClient,
                success,
                createExportTaskRequest,
                createExportTaskResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FCreateLogGroupAction : public FPendingLatentAction {
private:
    bool &success;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::CreateLogGroupOutcomeCallable callable;

public:
    FCreateLogGroupAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FCreateLogGroupRequest createLogGroupRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->CreateLogGroupCallable(createLogGroupRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsCreateLogGroupOutcome = callable.get();

            success = awsCreateLogGroupOutcome.IsSuccess();

                errorType = fromAWS(awsCreateLogGroupOutcome.GetError().GetErrorType());
                errorMessage = ("CreateLogGroup error: " + awsCreateLogGroupOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("CreateLogGroup Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::CreateLogGroup(
    UObject *WorldContextObject,
    bool &success,
    FCreateLogGroupRequest createLogGroupRequest,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FCreateLogGroupAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FCreateLogGroupAction(this->awsCloudWatchLogsClient,
                success,
                createLogGroupRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FCreateLogStreamAction : public FPendingLatentAction {
private:
    bool &success;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::CreateLogStreamOutcomeCallable callable;

public:
    FCreateLogStreamAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FCreateLogStreamRequest createLogStreamRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->CreateLogStreamCallable(createLogStreamRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsCreateLogStreamOutcome = callable.get();

            success = awsCreateLogStreamOutcome.IsSuccess();

                errorType = fromAWS(awsCreateLogStreamOutcome.GetError().GetErrorType());
                errorMessage = ("CreateLogStream error: " + awsCreateLogStreamOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("CreateLogStream Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::CreateLogStream(
    UObject *WorldContextObject,
    bool &success,
    FCreateLogStreamRequest createLogStreamRequest,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FCreateLogStreamAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FCreateLogStreamAction(this->awsCloudWatchLogsClient,
                success,
                createLogStreamRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FDeleteDataProtectionPolicyAction : public FPendingLatentAction {
private:
    bool &success;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::DeleteDataProtectionPolicyOutcomeCallable callable;

public:
    FDeleteDataProtectionPolicyAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FAWSCloudWatchLogsDeleteDataProtectionPolicyRequest deleteDataProtectionPolicyRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->DeleteDataProtectionPolicyCallable(deleteDataProtectionPolicyRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsDeleteDataProtectionPolicyOutcome = callable.get();

            success = awsDeleteDataProtectionPolicyOutcome.IsSuccess();

                errorType = fromAWS(awsDeleteDataProtectionPolicyOutcome.GetError().GetErrorType());
                errorMessage = ("DeleteDataProtectionPolicy error: " + awsDeleteDataProtectionPolicyOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DeleteDataProtectionPolicy Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::DeleteDataProtectionPolicy(
        UObject *WorldContextObject,
        bool &success,
        FAWSCloudWatchLogsDeleteDataProtectionPolicyRequest deleteDataProtectionPolicyRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteDataProtectionPolicyAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDeleteDataProtectionPolicyAction(this->awsCloudWatchLogsClient,
                success,
                deleteDataProtectionPolicyRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FDeleteDestinationAction : public FPendingLatentAction {
private:
    bool &success;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::DeleteDestinationOutcomeCallable callable;

public:
    FDeleteDestinationAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FDeleteDestinationRequest deleteDestinationRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->DeleteDestinationCallable(deleteDestinationRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsDeleteDestinationOutcome = callable.get();

            success = awsDeleteDestinationOutcome.IsSuccess();

                errorType = fromAWS(awsDeleteDestinationOutcome.GetError().GetErrorType());
                errorMessage = ("DeleteDestination error: " + awsDeleteDestinationOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DeleteDestination Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::DeleteDestination(
    UObject *WorldContextObject,
    bool &success,
    FDeleteDestinationRequest deleteDestinationRequest,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteDestinationAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDeleteDestinationAction(this->awsCloudWatchLogsClient,
                success,
                deleteDestinationRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FDeleteLogGroupAction : public FPendingLatentAction {
private:
    bool &success;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::DeleteLogGroupOutcomeCallable callable;

public:
    FDeleteLogGroupAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FDeleteLogGroupRequest deleteLogGroupRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->DeleteLogGroupCallable(deleteLogGroupRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsDeleteLogGroupOutcome = callable.get();

            success = awsDeleteLogGroupOutcome.IsSuccess();

                errorType = fromAWS(awsDeleteLogGroupOutcome.GetError().GetErrorType());
                errorMessage = ("DeleteLogGroup error: " + awsDeleteLogGroupOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DeleteLogGroup Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::DeleteLogGroup(
    UObject *WorldContextObject,
    bool &success,
    FDeleteLogGroupRequest deleteLogGroupRequest,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteLogGroupAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDeleteLogGroupAction(this->awsCloudWatchLogsClient,
                success,
                deleteLogGroupRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FDeleteLogStreamAction : public FPendingLatentAction {
private:
    bool &success;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::DeleteLogStreamOutcomeCallable callable;

public:
    FDeleteLogStreamAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FDeleteLogStreamRequest deleteLogStreamRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->DeleteLogStreamCallable(deleteLogStreamRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsDeleteLogStreamOutcome = callable.get();

            success = awsDeleteLogStreamOutcome.IsSuccess();

                errorType = fromAWS(awsDeleteLogStreamOutcome.GetError().GetErrorType());
                errorMessage = ("DeleteLogStream error: " + awsDeleteLogStreamOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DeleteLogStream Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::DeleteLogStream(
    UObject *WorldContextObject,
    bool &success,
    FDeleteLogStreamRequest deleteLogStreamRequest,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteLogStreamAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDeleteLogStreamAction(this->awsCloudWatchLogsClient,
                success,
                deleteLogStreamRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FDeleteMetricFilterAction : public FPendingLatentAction {
private:
    bool &success;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::DeleteMetricFilterOutcomeCallable callable;

public:
    FDeleteMetricFilterAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FDeleteMetricFilterRequest deleteMetricFilterRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->DeleteMetricFilterCallable(deleteMetricFilterRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsDeleteMetricFilterOutcome = callable.get();

            success = awsDeleteMetricFilterOutcome.IsSuccess();

                errorType = fromAWS(awsDeleteMetricFilterOutcome.GetError().GetErrorType());
                errorMessage = ("DeleteMetricFilter error: " + awsDeleteMetricFilterOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DeleteMetricFilter Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::DeleteMetricFilter(
    UObject *WorldContextObject,
    bool &success,
    FDeleteMetricFilterRequest deleteMetricFilterRequest,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteMetricFilterAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDeleteMetricFilterAction(this->awsCloudWatchLogsClient,
                success,
                deleteMetricFilterRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FDeleteQueryDefinitionAction : public FPendingLatentAction {
private:
    bool &success;
    FDeleteQueryDefinitionResult &deleteQueryDefinitionResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::DeleteQueryDefinitionOutcomeCallable callable;

public:
    FDeleteQueryDefinitionAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FDeleteQueryDefinitionRequest deleteQueryDefinitionRequest,
        FDeleteQueryDefinitionResult &deleteQueryDefinitionResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), deleteQueryDefinitionResult(deleteQueryDefinitionResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->DeleteQueryDefinitionCallable(deleteQueryDefinitionRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsDeleteQueryDefinitionOutcome = callable.get();

            success = awsDeleteQueryDefinitionOutcome.IsSuccess();
                if (success) {
                    deleteQueryDefinitionResult.fromAWS(awsDeleteQueryDefinitionOutcome.GetResult());
                }

                errorType = fromAWS(awsDeleteQueryDefinitionOutcome.GetError().GetErrorType());
                errorMessage = ("DeleteQueryDefinition error: " + awsDeleteQueryDefinitionOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DeleteQueryDefinition Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::DeleteQueryDefinition(
    UObject *WorldContextObject,
    bool &success,
    FDeleteQueryDefinitionRequest deleteQueryDefinitionRequest,
    FDeleteQueryDefinitionResult &deleteQueryDefinitionResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteQueryDefinitionAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDeleteQueryDefinitionAction(this->awsCloudWatchLogsClient,
                success,
                deleteQueryDefinitionRequest,
                deleteQueryDefinitionResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FDeleteResourcePolicyAction : public FPendingLatentAction {
private:
    bool &success;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::DeleteResourcePolicyOutcomeCallable callable;

public:
    FDeleteResourcePolicyAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FDeleteResourcePolicyRequest deleteResourcePolicyRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->DeleteResourcePolicyCallable(deleteResourcePolicyRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsDeleteResourcePolicyOutcome = callable.get();

            success = awsDeleteResourcePolicyOutcome.IsSuccess();

                errorType = fromAWS(awsDeleteResourcePolicyOutcome.GetError().GetErrorType());
                errorMessage = ("DeleteResourcePolicy error: " + awsDeleteResourcePolicyOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DeleteResourcePolicy Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::DeleteResourcePolicy(
    UObject *WorldContextObject,
    bool &success,
    FDeleteResourcePolicyRequest deleteResourcePolicyRequest,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteResourcePolicyAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDeleteResourcePolicyAction(this->awsCloudWatchLogsClient,
                success,
                deleteResourcePolicyRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FDeleteRetentionPolicyAction : public FPendingLatentAction {
private:
    bool &success;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::DeleteRetentionPolicyOutcomeCallable callable;

public:
    FDeleteRetentionPolicyAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FDeleteRetentionPolicyRequest deleteRetentionPolicyRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->DeleteRetentionPolicyCallable(deleteRetentionPolicyRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsDeleteRetentionPolicyOutcome = callable.get();

            success = awsDeleteRetentionPolicyOutcome.IsSuccess();

                errorType = fromAWS(awsDeleteRetentionPolicyOutcome.GetError().GetErrorType());
                errorMessage = ("DeleteRetentionPolicy error: " + awsDeleteRetentionPolicyOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DeleteRetentionPolicy Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::DeleteRetentionPolicy(
    UObject *WorldContextObject,
    bool &success,
    FDeleteRetentionPolicyRequest deleteRetentionPolicyRequest,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteRetentionPolicyAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDeleteRetentionPolicyAction(this->awsCloudWatchLogsClient,
                success,
                deleteRetentionPolicyRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FDeleteSubscriptionFilterAction : public FPendingLatentAction {
private:
    bool &success;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::DeleteSubscriptionFilterOutcomeCallable callable;

public:
    FDeleteSubscriptionFilterAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FDeleteSubscriptionFilterRequest deleteSubscriptionFilterRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->DeleteSubscriptionFilterCallable(deleteSubscriptionFilterRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsDeleteSubscriptionFilterOutcome = callable.get();

            success = awsDeleteSubscriptionFilterOutcome.IsSuccess();

                errorType = fromAWS(awsDeleteSubscriptionFilterOutcome.GetError().GetErrorType());
                errorMessage = ("DeleteSubscriptionFilter error: " + awsDeleteSubscriptionFilterOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DeleteSubscriptionFilter Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::DeleteSubscriptionFilter(
    UObject *WorldContextObject,
    bool &success,
    FDeleteSubscriptionFilterRequest deleteSubscriptionFilterRequest,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDeleteSubscriptionFilterAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDeleteSubscriptionFilterAction(this->awsCloudWatchLogsClient,
                success,
                deleteSubscriptionFilterRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FDescribeDestinationsAction : public FPendingLatentAction {
private:
    bool &success;
    FDescribeDestinationsResult &describeDestinationsResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::DescribeDestinationsOutcomeCallable callable;

public:
    FDescribeDestinationsAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FDescribeDestinationsRequest describeDestinationsRequest,
        FDescribeDestinationsResult &describeDestinationsResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), describeDestinationsResult(describeDestinationsResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->DescribeDestinationsCallable(describeDestinationsRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsDescribeDestinationsOutcome = callable.get();

            success = awsDescribeDestinationsOutcome.IsSuccess();
                if (success) {
                    describeDestinationsResult.fromAWS(awsDescribeDestinationsOutcome.GetResult());
                }

                errorType = fromAWS(awsDescribeDestinationsOutcome.GetError().GetErrorType());
                errorMessage = ("DescribeDestinations error: " + awsDescribeDestinationsOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DescribeDestinations Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::DescribeDestinations(
    UObject *WorldContextObject,
    bool &success,
    FDescribeDestinationsRequest describeDestinationsRequest,
    FDescribeDestinationsResult &describeDestinationsResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeDestinationsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDescribeDestinationsAction(this->awsCloudWatchLogsClient,
                success,
                describeDestinationsRequest,
                describeDestinationsResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FDescribeExportTasksAction : public FPendingLatentAction {
private:
    bool &success;
    FDescribeExportTasksResult &describeExportTasksResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::DescribeExportTasksOutcomeCallable callable;

public:
    FDescribeExportTasksAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FDescribeExportTasksRequest describeExportTasksRequest,
        FDescribeExportTasksResult &describeExportTasksResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), describeExportTasksResult(describeExportTasksResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->DescribeExportTasksCallable(describeExportTasksRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsDescribeExportTasksOutcome = callable.get();

            success = awsDescribeExportTasksOutcome.IsSuccess();
                if (success) {
                    describeExportTasksResult.fromAWS(awsDescribeExportTasksOutcome.GetResult());
                }

                errorType = fromAWS(awsDescribeExportTasksOutcome.GetError().GetErrorType());
                errorMessage = ("DescribeExportTasks error: " + awsDescribeExportTasksOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DescribeExportTasks Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::DescribeExportTasks(
    UObject *WorldContextObject,
    bool &success,
    FDescribeExportTasksRequest describeExportTasksRequest,
    FDescribeExportTasksResult &describeExportTasksResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeExportTasksAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDescribeExportTasksAction(this->awsCloudWatchLogsClient,
                success,
                describeExportTasksRequest,
                describeExportTasksResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FDescribeLogGroupsAction : public FPendingLatentAction {
private:
    bool &success;
    FDescribeLogGroupsResult &describeLogGroupsResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::DescribeLogGroupsOutcomeCallable callable;

public:
    FDescribeLogGroupsAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FDescribeLogGroupsRequest describeLogGroupsRequest,
        FDescribeLogGroupsResult &describeLogGroupsResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), describeLogGroupsResult(describeLogGroupsResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->DescribeLogGroupsCallable(describeLogGroupsRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsDescribeLogGroupsOutcome = callable.get();

            success = awsDescribeLogGroupsOutcome.IsSuccess();
                if (success) {
                    describeLogGroupsResult.fromAWS(awsDescribeLogGroupsOutcome.GetResult());
                }

                errorType = fromAWS(awsDescribeLogGroupsOutcome.GetError().GetErrorType());
                errorMessage = ("DescribeLogGroups error: " + awsDescribeLogGroupsOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DescribeLogGroups Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::DescribeLogGroups(
    UObject *WorldContextObject,
    bool &success,
    FDescribeLogGroupsRequest describeLogGroupsRequest,
    FDescribeLogGroupsResult &describeLogGroupsResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeLogGroupsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDescribeLogGroupsAction(this->awsCloudWatchLogsClient,
                success,
                describeLogGroupsRequest,
                describeLogGroupsResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FDescribeLogStreamsAction : public FPendingLatentAction {
private:
    bool &success;
    FDescribeLogStreamsResult &describeLogStreamsResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::DescribeLogStreamsOutcomeCallable callable;

public:
    FDescribeLogStreamsAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FDescribeLogStreamsRequest describeLogStreamsRequest,
        FDescribeLogStreamsResult &describeLogStreamsResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), describeLogStreamsResult(describeLogStreamsResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->DescribeLogStreamsCallable(describeLogStreamsRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsDescribeLogStreamsOutcome = callable.get();

            success = awsDescribeLogStreamsOutcome.IsSuccess();
                if (success) {
                    describeLogStreamsResult.fromAWS(awsDescribeLogStreamsOutcome.GetResult());
                }

                errorType = fromAWS(awsDescribeLogStreamsOutcome.GetError().GetErrorType());
                errorMessage = ("DescribeLogStreams error: " + awsDescribeLogStreamsOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DescribeLogStreams Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::DescribeLogStreams(
    UObject *WorldContextObject,
    bool &success,
    FDescribeLogStreamsRequest describeLogStreamsRequest,
    FDescribeLogStreamsResult &describeLogStreamsResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeLogStreamsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDescribeLogStreamsAction(this->awsCloudWatchLogsClient,
                success,
                describeLogStreamsRequest,
                describeLogStreamsResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FDescribeMetricFiltersAction : public FPendingLatentAction {
private:
    bool &success;
    FDescribeMetricFiltersResult &describeMetricFiltersResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::DescribeMetricFiltersOutcomeCallable callable;

public:
    FDescribeMetricFiltersAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FDescribeMetricFiltersRequest describeMetricFiltersRequest,
        FDescribeMetricFiltersResult &describeMetricFiltersResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), describeMetricFiltersResult(describeMetricFiltersResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->DescribeMetricFiltersCallable(describeMetricFiltersRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsDescribeMetricFiltersOutcome = callable.get();

            success = awsDescribeMetricFiltersOutcome.IsSuccess();
                if (success) {
                    describeMetricFiltersResult.fromAWS(awsDescribeMetricFiltersOutcome.GetResult());
                }

                errorType = fromAWS(awsDescribeMetricFiltersOutcome.GetError().GetErrorType());
                errorMessage = ("DescribeMetricFilters error: " + awsDescribeMetricFiltersOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DescribeMetricFilters Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::DescribeMetricFilters(
    UObject *WorldContextObject,
    bool &success,
    FDescribeMetricFiltersRequest describeMetricFiltersRequest,
    FDescribeMetricFiltersResult &describeMetricFiltersResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeMetricFiltersAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDescribeMetricFiltersAction(this->awsCloudWatchLogsClient,
                success,
                describeMetricFiltersRequest,
                describeMetricFiltersResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FDescribeQueriesAction : public FPendingLatentAction {
private:
    bool &success;
    FDescribeQueriesResult &describeQueriesResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::DescribeQueriesOutcomeCallable callable;

public:
    FDescribeQueriesAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FDescribeQueriesRequest describeQueriesRequest,
        FDescribeQueriesResult &describeQueriesResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), describeQueriesResult(describeQueriesResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->DescribeQueriesCallable(describeQueriesRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsDescribeQueriesOutcome = callable.get();

            success = awsDescribeQueriesOutcome.IsSuccess();
                if (success) {
                    describeQueriesResult.fromAWS(awsDescribeQueriesOutcome.GetResult());
                }

                errorType = fromAWS(awsDescribeQueriesOutcome.GetError().GetErrorType());
                errorMessage = ("DescribeQueries error: " + awsDescribeQueriesOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DescribeQueries Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::DescribeQueries(
    UObject *WorldContextObject,
    bool &success,
    FDescribeQueriesRequest describeQueriesRequest,
    FDescribeQueriesResult &describeQueriesResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeQueriesAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDescribeQueriesAction(this->awsCloudWatchLogsClient,
                success,
                describeQueriesRequest,
                describeQueriesResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FDescribeQueryDefinitionsAction : public FPendingLatentAction {
private:
    bool &success;
    FDescribeQueryDefinitionsResult &describeQueryDefinitionsResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::DescribeQueryDefinitionsOutcomeCallable callable;

public:
    FDescribeQueryDefinitionsAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FDescribeQueryDefinitionsRequest describeQueryDefinitionsRequest,
        FDescribeQueryDefinitionsResult &describeQueryDefinitionsResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), describeQueryDefinitionsResult(describeQueryDefinitionsResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->DescribeQueryDefinitionsCallable(describeQueryDefinitionsRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsDescribeQueryDefinitionsOutcome = callable.get();

            success = awsDescribeQueryDefinitionsOutcome.IsSuccess();
                if (success) {
                    describeQueryDefinitionsResult.fromAWS(awsDescribeQueryDefinitionsOutcome.GetResult());
                }

                errorType = fromAWS(awsDescribeQueryDefinitionsOutcome.GetError().GetErrorType());
                errorMessage = ("DescribeQueryDefinitions error: " + awsDescribeQueryDefinitionsOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DescribeQueryDefinitions Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::DescribeQueryDefinitions(
    UObject *WorldContextObject,
    bool &success,
    FDescribeQueryDefinitionsRequest describeQueryDefinitionsRequest,
    FDescribeQueryDefinitionsResult &describeQueryDefinitionsResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeQueryDefinitionsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDescribeQueryDefinitionsAction(this->awsCloudWatchLogsClient,
                success,
                describeQueryDefinitionsRequest,
                describeQueryDefinitionsResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FDescribeResourcePoliciesAction : public FPendingLatentAction {
private:
    bool &success;
    FDescribeResourcePoliciesResult &describeResourcePoliciesResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::DescribeResourcePoliciesOutcomeCallable callable;

public:
    FDescribeResourcePoliciesAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FDescribeResourcePoliciesRequest describeResourcePoliciesRequest,
        FDescribeResourcePoliciesResult &describeResourcePoliciesResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), describeResourcePoliciesResult(describeResourcePoliciesResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->DescribeResourcePoliciesCallable(describeResourcePoliciesRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsDescribeResourcePoliciesOutcome = callable.get();

            success = awsDescribeResourcePoliciesOutcome.IsSuccess();
                if (success) {
                    describeResourcePoliciesResult.fromAWS(awsDescribeResourcePoliciesOutcome.GetResult());
                }

                errorType = fromAWS(awsDescribeResourcePoliciesOutcome.GetError().GetErrorType());
                errorMessage = ("DescribeResourcePolicies error: " + awsDescribeResourcePoliciesOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DescribeResourcePolicies Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::DescribeResourcePolicies(
    UObject *WorldContextObject,
    bool &success,
    FDescribeResourcePoliciesRequest describeResourcePoliciesRequest,
    FDescribeResourcePoliciesResult &describeResourcePoliciesResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeResourcePoliciesAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDescribeResourcePoliciesAction(this->awsCloudWatchLogsClient,
                success,
                describeResourcePoliciesRequest,
                describeResourcePoliciesResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FDescribeSubscriptionFiltersAction : public FPendingLatentAction {
private:
    bool &success;
    FDescribeSubscriptionFiltersResult &describeSubscriptionFiltersResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::DescribeSubscriptionFiltersOutcomeCallable callable;

public:
    FDescribeSubscriptionFiltersAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FDescribeSubscriptionFiltersRequest describeSubscriptionFiltersRequest,
        FDescribeSubscriptionFiltersResult &describeSubscriptionFiltersResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), describeSubscriptionFiltersResult(describeSubscriptionFiltersResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->DescribeSubscriptionFiltersCallable(describeSubscriptionFiltersRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsDescribeSubscriptionFiltersOutcome = callable.get();

            success = awsDescribeSubscriptionFiltersOutcome.IsSuccess();
                if (success) {
                    describeSubscriptionFiltersResult.fromAWS(awsDescribeSubscriptionFiltersOutcome.GetResult());
                }

                errorType = fromAWS(awsDescribeSubscriptionFiltersOutcome.GetError().GetErrorType());
                errorMessage = ("DescribeSubscriptionFilters error: " + awsDescribeSubscriptionFiltersOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DescribeSubscriptionFilters Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::DescribeSubscriptionFilters(
    UObject *WorldContextObject,
    bool &success,
    FDescribeSubscriptionFiltersRequest describeSubscriptionFiltersRequest,
    FDescribeSubscriptionFiltersResult &describeSubscriptionFiltersResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDescribeSubscriptionFiltersAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDescribeSubscriptionFiltersAction(this->awsCloudWatchLogsClient,
                success,
                describeSubscriptionFiltersRequest,
                describeSubscriptionFiltersResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FDisassociateKmsKeyAction : public FPendingLatentAction {
private:
    bool &success;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::DisassociateKmsKeyOutcomeCallable callable;

public:
    FDisassociateKmsKeyAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FDisassociateKmsKeyRequest disassociateKmsKeyRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->DisassociateKmsKeyCallable(disassociateKmsKeyRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsDisassociateKmsKeyOutcome = callable.get();

            success = awsDisassociateKmsKeyOutcome.IsSuccess();

                errorType = fromAWS(awsDisassociateKmsKeyOutcome.GetError().GetErrorType());
                errorMessage = ("DisassociateKmsKey error: " + awsDisassociateKmsKeyOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("DisassociateKmsKey Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::DisassociateKmsKey(
    UObject *WorldContextObject,
    bool &success,
    FDisassociateKmsKeyRequest disassociateKmsKeyRequest,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FDisassociateKmsKeyAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FDisassociateKmsKeyAction(this->awsCloudWatchLogsClient,
                success,
                disassociateKmsKeyRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FFilterLogEventsAction : public FPendingLatentAction {
private:
    bool &success;
    FFilterLogEventsResult &filterLogEventsResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::FilterLogEventsOutcomeCallable callable;

public:
    FFilterLogEventsAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FFilterLogEventsRequest filterLogEventsRequest,
        FFilterLogEventsResult &filterLogEventsResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), filterLogEventsResult(filterLogEventsResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->FilterLogEventsCallable(filterLogEventsRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsFilterLogEventsOutcome = callable.get();

            success = awsFilterLogEventsOutcome.IsSuccess();
                if (success) {
                    filterLogEventsResult.fromAWS(awsFilterLogEventsOutcome.GetResult());
                }

                errorType = fromAWS(awsFilterLogEventsOutcome.GetError().GetErrorType());
                errorMessage = ("FilterLogEvents error: " + awsFilterLogEventsOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("FilterLogEvents Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::FilterLogEvents(
    UObject *WorldContextObject,
    bool &success,
    FFilterLogEventsRequest filterLogEventsRequest,
    FFilterLogEventsResult &filterLogEventsResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FFilterLogEventsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FFilterLogEventsAction(this->awsCloudWatchLogsClient,
                success,
                filterLogEventsRequest,
                filterLogEventsResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FGetDataProtectionPolicyAction : public FPendingLatentAction {
private:
    bool &success;
    FAWSCloudWatchLogsGetDataProtectionPolicyResult &getDataProtectionPolicyResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::GetDataProtectionPolicyOutcomeCallable callable;

public:
    FGetDataProtectionPolicyAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FAWSCloudWatchLogsGetDataProtectionPolicyRequest getDataProtectionPolicyRequest,
        FAWSCloudWatchLogsGetDataProtectionPolicyResult &getDataProtectionPolicyResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), getDataProtectionPolicyResult(getDataProtectionPolicyResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->GetDataProtectionPolicyCallable(getDataProtectionPolicyRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsGetDataProtectionPolicyOutcome = callable.get();

            success = awsGetDataProtectionPolicyOutcome.IsSuccess();
                if (success) {
                    getDataProtectionPolicyResult.fromAWS(awsGetDataProtectionPolicyOutcome.GetResult());
                }

                errorType = fromAWS(awsGetDataProtectionPolicyOutcome.GetError().GetErrorType());
                errorMessage = ("GetDataProtectionPolicy error: " + awsGetDataProtectionPolicyOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("GetDataProtectionPolicy Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::GetDataProtectionPolicy(
        UObject *WorldContextObject,
        bool &success,
        FAWSCloudWatchLogsGetDataProtectionPolicyRequest getDataProtectionPolicyRequest,
        FAWSCloudWatchLogsGetDataProtectionPolicyResult &getDataProtectionPolicyResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FGetDataProtectionPolicyAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FGetDataProtectionPolicyAction(this->awsCloudWatchLogsClient,
                success,
                getDataProtectionPolicyRequest,
                getDataProtectionPolicyResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FGetLogEventsAction : public FPendingLatentAction {
private:
    bool &success;
    FGetLogEventsResult &getLogEventsResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::GetLogEventsOutcomeCallable callable;

public:
    FGetLogEventsAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FGetLogEventsRequest getLogEventsRequest,
        FGetLogEventsResult &getLogEventsResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), getLogEventsResult(getLogEventsResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->GetLogEventsCallable(getLogEventsRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsGetLogEventsOutcome = callable.get();

            success = awsGetLogEventsOutcome.IsSuccess();
                if (success) {
                    getLogEventsResult.fromAWS(awsGetLogEventsOutcome.GetResult());
                }

                errorType = fromAWS(awsGetLogEventsOutcome.GetError().GetErrorType());
                errorMessage = ("GetLogEvents error: " + awsGetLogEventsOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("GetLogEvents Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::GetLogEvents(
    UObject *WorldContextObject,
    bool &success,
    FGetLogEventsRequest getLogEventsRequest,
    FGetLogEventsResult &getLogEventsResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FGetLogEventsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FGetLogEventsAction(this->awsCloudWatchLogsClient,
                success,
                getLogEventsRequest,
                getLogEventsResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FGetLogGroupFieldsAction : public FPendingLatentAction {
private:
    bool &success;
    FGetLogGroupFieldsResult &getLogGroupFieldsResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::GetLogGroupFieldsOutcomeCallable callable;

public:
    FGetLogGroupFieldsAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FGetLogGroupFieldsRequest getLogGroupFieldsRequest,
        FGetLogGroupFieldsResult &getLogGroupFieldsResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), getLogGroupFieldsResult(getLogGroupFieldsResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->GetLogGroupFieldsCallable(getLogGroupFieldsRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsGetLogGroupFieldsOutcome = callable.get();

            success = awsGetLogGroupFieldsOutcome.IsSuccess();
                if (success) {
                    getLogGroupFieldsResult.fromAWS(awsGetLogGroupFieldsOutcome.GetResult());
                }

                errorType = fromAWS(awsGetLogGroupFieldsOutcome.GetError().GetErrorType());
                errorMessage = ("GetLogGroupFields error: " + awsGetLogGroupFieldsOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("GetLogGroupFields Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::GetLogGroupFields(
    UObject *WorldContextObject,
    bool &success,
    FGetLogGroupFieldsRequest getLogGroupFieldsRequest,
    FGetLogGroupFieldsResult &getLogGroupFieldsResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FGetLogGroupFieldsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FGetLogGroupFieldsAction(this->awsCloudWatchLogsClient,
                success,
                getLogGroupFieldsRequest,
                getLogGroupFieldsResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FGetLogRecordAction : public FPendingLatentAction {
private:
    bool &success;
    FGetLogRecordResult &getLogRecordResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::GetLogRecordOutcomeCallable callable;

public:
    FGetLogRecordAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FGetLogRecordRequest getLogRecordRequest,
        FGetLogRecordResult &getLogRecordResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), getLogRecordResult(getLogRecordResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->GetLogRecordCallable(getLogRecordRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsGetLogRecordOutcome = callable.get();

            success = awsGetLogRecordOutcome.IsSuccess();
                if (success) {
                    getLogRecordResult.fromAWS(awsGetLogRecordOutcome.GetResult());
                }

                errorType = fromAWS(awsGetLogRecordOutcome.GetError().GetErrorType());
                errorMessage = ("GetLogRecord error: " + awsGetLogRecordOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("GetLogRecord Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::GetLogRecord(
    UObject *WorldContextObject,
    bool &success,
    FGetLogRecordRequest getLogRecordRequest,
    FGetLogRecordResult &getLogRecordResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FGetLogRecordAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FGetLogRecordAction(this->awsCloudWatchLogsClient,
                success,
                getLogRecordRequest,
                getLogRecordResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FGetQueryResultsAction : public FPendingLatentAction {
private:
    bool &success;
    FGetQueryResultsResult &getQueryResultsResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::GetQueryResultsOutcomeCallable callable;

public:
    FGetQueryResultsAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FGetQueryResultsRequest getQueryResultsRequest,
        FGetQueryResultsResult &getQueryResultsResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), getQueryResultsResult(getQueryResultsResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->GetQueryResultsCallable(getQueryResultsRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsGetQueryResultsOutcome = callable.get();

            success = awsGetQueryResultsOutcome.IsSuccess();
                if (success) {
                    getQueryResultsResult.fromAWS(awsGetQueryResultsOutcome.GetResult());
                }

                errorType = fromAWS(awsGetQueryResultsOutcome.GetError().GetErrorType());
                errorMessage = ("GetQueryResults error: " + awsGetQueryResultsOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("GetQueryResults Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::GetQueryResults(
    UObject *WorldContextObject,
    bool &success,
    FGetQueryResultsRequest getQueryResultsRequest,
    FGetQueryResultsResult &getQueryResultsResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FGetQueryResultsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FGetQueryResultsAction(this->awsCloudWatchLogsClient,
                success,
                getQueryResultsRequest,
                getQueryResultsResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FListTagsForResourceAction : public FPendingLatentAction {
private:
    bool &success;
    FAWSCloudWatchLogsListTagsForResourceResult &listTagsForResourceResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::ListTagsForResourceOutcomeCallable callable;

public:
    FListTagsForResourceAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FAWSCloudWatchLogsListTagsForResourceRequest listTagsForResourceRequest,
        FAWSCloudWatchLogsListTagsForResourceResult &listTagsForResourceResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), listTagsForResourceResult(listTagsForResourceResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->ListTagsForResourceCallable(listTagsForResourceRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsListTagsForResourceOutcome = callable.get();

            success = awsListTagsForResourceOutcome.IsSuccess();
                if (success) {
                    listTagsForResourceResult.fromAWS(awsListTagsForResourceOutcome.GetResult());
                }

                errorType = fromAWS(awsListTagsForResourceOutcome.GetError().GetErrorType());
                errorMessage = ("ListTagsForResource error: " + awsListTagsForResourceOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("ListTagsForResource Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::ListTagsForResource(
    UObject *WorldContextObject,
    bool &success,
    FAWSCloudWatchLogsListTagsForResourceRequest listTagsForResourceRequest,
    FAWSCloudWatchLogsListTagsForResourceResult &listTagsForResourceResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FListTagsForResourceAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FListTagsForResourceAction(this->awsCloudWatchLogsClient,
                success,
                listTagsForResourceRequest,
                listTagsForResourceResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FPutDataProtectionPolicyAction : public FPendingLatentAction {
private:
    bool &success;
    FAWSCloudWatchLogsPutDataProtectionPolicyResult &putDataProtectionPolicyResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::PutDataProtectionPolicyOutcomeCallable callable;

public:
    FPutDataProtectionPolicyAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FAWSCloudWatchLogsPutDataProtectionPolicyRequest putDataProtectionPolicyRequest,
        FAWSCloudWatchLogsPutDataProtectionPolicyResult &putDataProtectionPolicyResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), putDataProtectionPolicyResult(putDataProtectionPolicyResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->PutDataProtectionPolicyCallable(putDataProtectionPolicyRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsPutDataProtectionPolicyOutcome = callable.get();

            success = awsPutDataProtectionPolicyOutcome.IsSuccess();
                if (success) {
                    putDataProtectionPolicyResult.fromAWS(awsPutDataProtectionPolicyOutcome.GetResult());
                }

                errorType = fromAWS(awsPutDataProtectionPolicyOutcome.GetError().GetErrorType());
                errorMessage = ("PutDataProtectionPolicy error: " + awsPutDataProtectionPolicyOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("PutDataProtectionPolicy Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::PutDataProtectionPolicy(
        UObject *WorldContextObject,
        bool &success,
        FAWSCloudWatchLogsPutDataProtectionPolicyRequest putDataProtectionPolicyRequest,
        FAWSCloudWatchLogsPutDataProtectionPolicyResult &putDataProtectionPolicyResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FPutDataProtectionPolicyAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FPutDataProtectionPolicyAction(this->awsCloudWatchLogsClient,
                success,
                putDataProtectionPolicyRequest,
                putDataProtectionPolicyResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FPutDestinationAction : public FPendingLatentAction {
private:
    bool &success;
    FPutDestinationResult &putDestinationResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::PutDestinationOutcomeCallable callable;

public:
    FPutDestinationAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FPutDestinationRequest putDestinationRequest,
        FPutDestinationResult &putDestinationResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), putDestinationResult(putDestinationResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->PutDestinationCallable(putDestinationRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsPutDestinationOutcome = callable.get();

            success = awsPutDestinationOutcome.IsSuccess();
                if (success) {
                    putDestinationResult.fromAWS(awsPutDestinationOutcome.GetResult());
                }

                errorType = fromAWS(awsPutDestinationOutcome.GetError().GetErrorType());
                errorMessage = ("PutDestination error: " + awsPutDestinationOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("PutDestination Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::PutDestination(
    UObject *WorldContextObject,
    bool &success,
    FPutDestinationRequest putDestinationRequest,
    FPutDestinationResult &putDestinationResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FPutDestinationAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FPutDestinationAction(this->awsCloudWatchLogsClient,
                success,
                putDestinationRequest,
                putDestinationResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FPutDestinationPolicyAction : public FPendingLatentAction {
private:
    bool &success;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::PutDestinationPolicyOutcomeCallable callable;

public:
    FPutDestinationPolicyAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FPutDestinationPolicyRequest putDestinationPolicyRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->PutDestinationPolicyCallable(putDestinationPolicyRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsPutDestinationPolicyOutcome = callable.get();

            success = awsPutDestinationPolicyOutcome.IsSuccess();

                errorType = fromAWS(awsPutDestinationPolicyOutcome.GetError().GetErrorType());
                errorMessage = ("PutDestinationPolicy error: " + awsPutDestinationPolicyOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("PutDestinationPolicy Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::PutDestinationPolicy(
    UObject *WorldContextObject,
    bool &success,
    FPutDestinationPolicyRequest putDestinationPolicyRequest,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FPutDestinationPolicyAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FPutDestinationPolicyAction(this->awsCloudWatchLogsClient,
                success,
                putDestinationPolicyRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FPutLogEventsAction : public FPendingLatentAction {
private:
    bool &success;
    FPutLogEventsResult &putLogEventsResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::PutLogEventsOutcomeCallable callable;

public:
    FPutLogEventsAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FPutLogEventsRequest putLogEventsRequest,
        FPutLogEventsResult &putLogEventsResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), putLogEventsResult(putLogEventsResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->PutLogEventsCallable(putLogEventsRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsPutLogEventsOutcome = callable.get();

            success = awsPutLogEventsOutcome.IsSuccess();
                if (success) {
                    putLogEventsResult.fromAWS(awsPutLogEventsOutcome.GetResult());
                }

                errorType = fromAWS(awsPutLogEventsOutcome.GetError().GetErrorType());
                errorMessage = ("PutLogEvents error: " + awsPutLogEventsOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("PutLogEvents Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::PutLogEvents(
    UObject *WorldContextObject,
    bool &success,
    FPutLogEventsRequest putLogEventsRequest,
    FPutLogEventsResult &putLogEventsResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FPutLogEventsAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FPutLogEventsAction(this->awsCloudWatchLogsClient,
                success,
                putLogEventsRequest,
                putLogEventsResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FPutMetricFilterAction : public FPendingLatentAction {
private:
    bool &success;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::PutMetricFilterOutcomeCallable callable;

public:
    FPutMetricFilterAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FPutMetricFilterRequest putMetricFilterRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->PutMetricFilterCallable(putMetricFilterRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsPutMetricFilterOutcome = callable.get();

            success = awsPutMetricFilterOutcome.IsSuccess();

                errorType = fromAWS(awsPutMetricFilterOutcome.GetError().GetErrorType());
                errorMessage = ("PutMetricFilter error: " + awsPutMetricFilterOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("PutMetricFilter Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::PutMetricFilter(
    UObject *WorldContextObject,
    bool &success,
    FPutMetricFilterRequest putMetricFilterRequest,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FPutMetricFilterAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FPutMetricFilterAction(this->awsCloudWatchLogsClient,
                success,
                putMetricFilterRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FPutQueryDefinitionAction : public FPendingLatentAction {
private:
    bool &success;
    FPutQueryDefinitionResult &putQueryDefinitionResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::PutQueryDefinitionOutcomeCallable callable;

public:
    FPutQueryDefinitionAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FPutQueryDefinitionRequest putQueryDefinitionRequest,
        FPutQueryDefinitionResult &putQueryDefinitionResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), putQueryDefinitionResult(putQueryDefinitionResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->PutQueryDefinitionCallable(putQueryDefinitionRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsPutQueryDefinitionOutcome = callable.get();

            success = awsPutQueryDefinitionOutcome.IsSuccess();
                if (success) {
                    putQueryDefinitionResult.fromAWS(awsPutQueryDefinitionOutcome.GetResult());
                }

                errorType = fromAWS(awsPutQueryDefinitionOutcome.GetError().GetErrorType());
                errorMessage = ("PutQueryDefinition error: " + awsPutQueryDefinitionOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("PutQueryDefinition Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::PutQueryDefinition(
    UObject *WorldContextObject,
    bool &success,
    FPutQueryDefinitionRequest putQueryDefinitionRequest,
    FPutQueryDefinitionResult &putQueryDefinitionResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FPutQueryDefinitionAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FPutQueryDefinitionAction(this->awsCloudWatchLogsClient,
                success,
                putQueryDefinitionRequest,
                putQueryDefinitionResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FPutResourcePolicyAction : public FPendingLatentAction {
private:
    bool &success;
    FPutResourcePolicyResult &putResourcePolicyResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::PutResourcePolicyOutcomeCallable callable;

public:
    FPutResourcePolicyAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FPutResourcePolicyRequest putResourcePolicyRequest,
        FPutResourcePolicyResult &putResourcePolicyResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), putResourcePolicyResult(putResourcePolicyResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->PutResourcePolicyCallable(putResourcePolicyRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsPutResourcePolicyOutcome = callable.get();

            success = awsPutResourcePolicyOutcome.IsSuccess();
                if (success) {
                    putResourcePolicyResult.fromAWS(awsPutResourcePolicyOutcome.GetResult());
                }

                errorType = fromAWS(awsPutResourcePolicyOutcome.GetError().GetErrorType());
                errorMessage = ("PutResourcePolicy error: " + awsPutResourcePolicyOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("PutResourcePolicy Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::PutResourcePolicy(
    UObject *WorldContextObject,
    bool &success,
    FPutResourcePolicyRequest putResourcePolicyRequest,
    FPutResourcePolicyResult &putResourcePolicyResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FPutResourcePolicyAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FPutResourcePolicyAction(this->awsCloudWatchLogsClient,
                success,
                putResourcePolicyRequest,
                putResourcePolicyResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FPutRetentionPolicyAction : public FPendingLatentAction {
private:
    bool &success;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::PutRetentionPolicyOutcomeCallable callable;

public:
    FPutRetentionPolicyAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FPutRetentionPolicyRequest putRetentionPolicyRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->PutRetentionPolicyCallable(putRetentionPolicyRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsPutRetentionPolicyOutcome = callable.get();

            success = awsPutRetentionPolicyOutcome.IsSuccess();

                errorType = fromAWS(awsPutRetentionPolicyOutcome.GetError().GetErrorType());
                errorMessage = ("PutRetentionPolicy error: " + awsPutRetentionPolicyOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("PutRetentionPolicy Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::PutRetentionPolicy(
    UObject *WorldContextObject,
    bool &success,
    FPutRetentionPolicyRequest putRetentionPolicyRequest,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FPutRetentionPolicyAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FPutRetentionPolicyAction(this->awsCloudWatchLogsClient,
                success,
                putRetentionPolicyRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FPutSubscriptionFilterAction : public FPendingLatentAction {
private:
    bool &success;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::PutSubscriptionFilterOutcomeCallable callable;

public:
    FPutSubscriptionFilterAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FPutSubscriptionFilterRequest putSubscriptionFilterRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->PutSubscriptionFilterCallable(putSubscriptionFilterRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsPutSubscriptionFilterOutcome = callable.get();

            success = awsPutSubscriptionFilterOutcome.IsSuccess();

                errorType = fromAWS(awsPutSubscriptionFilterOutcome.GetError().GetErrorType());
                errorMessage = ("PutSubscriptionFilter error: " + awsPutSubscriptionFilterOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("PutSubscriptionFilter Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::PutSubscriptionFilter(
    UObject *WorldContextObject,
    bool &success,
    FPutSubscriptionFilterRequest putSubscriptionFilterRequest,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FPutSubscriptionFilterAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FPutSubscriptionFilterAction(this->awsCloudWatchLogsClient,
                success,
                putSubscriptionFilterRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FStartQueryAction : public FPendingLatentAction {
private:
    bool &success;
    FStartQueryResult &startQueryResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::StartQueryOutcomeCallable callable;

public:
    FStartQueryAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FStartQueryRequest startQueryRequest,
        FStartQueryResult &startQueryResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), startQueryResult(startQueryResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->StartQueryCallable(startQueryRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsStartQueryOutcome = callable.get();

            success = awsStartQueryOutcome.IsSuccess();
                if (success) {
                    startQueryResult.fromAWS(awsStartQueryOutcome.GetResult());
                }

                errorType = fromAWS(awsStartQueryOutcome.GetError().GetErrorType());
                errorMessage = ("StartQuery error: " + awsStartQueryOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("StartQuery Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::StartQuery(
    UObject *WorldContextObject,
    bool &success,
    FStartQueryRequest startQueryRequest,
    FStartQueryResult &startQueryResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FStartQueryAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FStartQueryAction(this->awsCloudWatchLogsClient,
                success,
                startQueryRequest,
                startQueryResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FStopQueryAction : public FPendingLatentAction {
private:
    bool &success;
    FStopQueryResult &stopQueryResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::StopQueryOutcomeCallable callable;

public:
    FStopQueryAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FStopQueryRequest stopQueryRequest,
        FStopQueryResult &stopQueryResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), stopQueryResult(stopQueryResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->StopQueryCallable(stopQueryRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsStopQueryOutcome = callable.get();

            success = awsStopQueryOutcome.IsSuccess();
                if (success) {
                    stopQueryResult.fromAWS(awsStopQueryOutcome.GetResult());
                }

                errorType = fromAWS(awsStopQueryOutcome.GetError().GetErrorType());
                errorMessage = ("StopQuery error: " + awsStopQueryOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("StopQuery Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::StopQuery(
    UObject *WorldContextObject,
    bool &success,
    FStopQueryRequest stopQueryRequest,
    FStopQueryResult &stopQueryResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FStopQueryAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FStopQueryAction(this->awsCloudWatchLogsClient,
                success,
                stopQueryRequest,
                stopQueryResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FTagResourceAction : public FPendingLatentAction {
private:
    bool &success;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::TagResourceOutcomeCallable callable;

public:
    FTagResourceAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FAWSCloudWatchLogsTagResourceRequest tagResourceRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->TagResourceCallable(tagResourceRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsTagResourceOutcome = callable.get();

            success = awsTagResourceOutcome.IsSuccess();

            errorType = fromAWS(awsTagResourceOutcome.GetError().GetErrorType());
            errorMessage = ("TagResource error: " + awsTagResourceOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("TagResource Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::TagResource(
    UObject *WorldContextObject,
    bool &success,
    FAWSCloudWatchLogsTagResourceRequest tagResourceRequest,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FTagResourceAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FTagResourceAction(this->awsCloudWatchLogsClient,
                success,
                tagResourceRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FTestMetricFilterAction : public FPendingLatentAction {
private:
    bool &success;
    FTestMetricFilterResult &testMetricFilterResult;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::TestMetricFilterOutcomeCallable callable;

public:
    FTestMetricFilterAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FTestMetricFilterRequest testMetricFilterRequest,
        FTestMetricFilterResult &testMetricFilterResult,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), testMetricFilterResult(testMetricFilterResult), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->TestMetricFilterCallable(testMetricFilterRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsTestMetricFilterOutcome = callable.get();

            success = awsTestMetricFilterOutcome.IsSuccess();
                if (success) {
                    testMetricFilterResult.fromAWS(awsTestMetricFilterOutcome.GetResult());
                }

                errorType = fromAWS(awsTestMetricFilterOutcome.GetError().GetErrorType());
                errorMessage = ("TestMetricFilter error: " + awsTestMetricFilterOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("TestMetricFilter Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::TestMetricFilter(
    UObject *WorldContextObject,
    bool &success,
    FTestMetricFilterRequest testMetricFilterRequest,
    FTestMetricFilterResult &testMetricFilterResult,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FTestMetricFilterAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FTestMetricFilterAction(this->awsCloudWatchLogsClient,
                success,
                testMetricFilterRequest,
                testMetricFilterResult,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

class FUntagResourceAction : public FPendingLatentAction {
private:
    bool &success;
    ECloudWatchLogsError &errorType;
    FString &errorMessage;
    FName ExecutionFunction;
    int32 OutputLink;
    FWeakObjectPtr CallbackTarget;

    Aws::CloudWatchLogs::Model::UntagResourceOutcomeCallable callable;

public:
    FUntagResourceAction(
        Aws::CloudWatchLogs::CloudWatchLogsClient *LogsClient,
        bool &success,
        FAWSCloudWatchLogsUntagResourceRequest untagResourceRequest,
        ECloudWatchLogsError &errorType,
        FString &errorMessage,
        const FLatentActionInfo &LatentInfo
    )
    : success(success), errorType(errorType), errorMessage(errorMessage),
    ExecutionFunction(LatentInfo.ExecutionFunction),
    OutputLink(LatentInfo.Linkage), CallbackTarget(LatentInfo.CallbackTarget) {

        callable = LogsClient->UntagResourceCallable(untagResourceRequest.toAWS());
    }

    void UpdateOperation(FLatentResponse &Response) override {
        if (callable.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            auto awsUntagResourceOutcome = callable.get();

            success = awsUntagResourceOutcome.IsSuccess();

                errorType = fromAWS(awsUntagResourceOutcome.GetError().GetErrorType());
                errorMessage = ("UntagResource error: " + awsUntagResourceOutcome.GetError().GetMessage()).c_str();

            Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
        } else {
            Response.FinishAndTriggerIf(false, ExecutionFunction, OutputLink, CallbackTarget);
        }
    }

#if WITH_EDITOR

    // Returns a human readable description of the latent operation's current state
    FString GetDescription() const override {
        return FString("UntagResource Request");
    }

#endif
};

#endif

void
UCloudWatchLogsClientObject::UntagResource(
    UObject *WorldContextObject,
    bool &success,
    FAWSCloudWatchLogsUntagResourceRequest untagResourceRequest,
    ECloudWatchLogsError &errorType,
    FString &errorMessage,
    struct FLatentActionInfo LatentInfo
) {
#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
    // Prepare latent action
    if (UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert)) {
        FLatentActionManager &LatentActionManager = World->GetLatentActionManager();
        if (LatentActionManager.FindExistingAction<FUntagResourceAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL) {
            LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID,
                new FUntagResourceAction(this->awsCloudWatchLogsClient,
                success,
                untagResourceRequest,
                errorType,
                errorMessage,
                LatentInfo));
        }
    }
    return;
#endif
    return;
}
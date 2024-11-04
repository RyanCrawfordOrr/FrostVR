/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DisassociateKmsKeyRequest.h"

#endif

#include "DisassociateKmsKeyRequest.generated.h"

USTRUCT(BlueprintType)
struct FDisassociateKmsKeyRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::DisassociateKmsKeyRequest toAWS() const {
        Aws::CloudWatchLogs::Model::DisassociateKmsKeyRequest awsDisassociateKmsKeyRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsDisassociateKmsKeyRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

        return awsDisassociateKmsKeyRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty();
    }
#endif
};

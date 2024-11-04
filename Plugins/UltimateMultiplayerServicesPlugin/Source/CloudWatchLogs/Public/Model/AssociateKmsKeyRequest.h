/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/AssociateKmsKeyRequest.h"

#endif

#include "AssociateKmsKeyRequest.generated.h"

USTRUCT(BlueprintType)
struct FAssociateKmsKeyRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    *  <p>The Amazon Resource Name (ARN) of the CMK to use when encrypting log data. This must be a symmetric CMK. For more information, see <a href="https://docs.aws.amazon.com/general/latest/gr/aws-arns-and-namespaces.html#arn-syntax-kms">Amazon Resource Names - AWS Key Management Service (AWS KMS)</a> and <a href="https://docs.aws.amazon.com/kms/latest/developerguide/symmetric-asymmetric.html">Using Symmetric and Asymmetric Keys</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString kmsKeyId;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::AssociateKmsKeyRequest toAWS() const {
        Aws::CloudWatchLogs::Model::AssociateKmsKeyRequest awsAssociateKmsKeyRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsAssociateKmsKeyRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

		if (!(this->kmsKeyId.IsEmpty())) {
            awsAssociateKmsKeyRequest.SetKmsKeyId(TCHAR_TO_UTF8(*this->kmsKeyId));
        }

        return awsAssociateKmsKeyRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty() && this->kmsKeyId.IsEmpty();
    }
#endif
};

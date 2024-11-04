/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/CreateLogGroupRequest.h"

#endif

#include "CreateLogGroupRequest.generated.h"

USTRUCT(BlueprintType)
struct FCreateLogGroupRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    *  <p>The Amazon Resource Name (ARN) of the CMK to use when encrypting log data. For more information, see <a href="https://docs.aws.amazon.com/general/latest/gr/aws-arns-and-namespaces.html#arn-syntax-kms">Amazon Resource Names - AWS Key Management Service (AWS KMS)</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString kmsKeyId;

    /**
    *  <p>The key-value pairs to use for the tags.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TMap<FString, FString> tags;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::CreateLogGroupRequest toAWS() const {
        Aws::CloudWatchLogs::Model::CreateLogGroupRequest awsCreateLogGroupRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsCreateLogGroupRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

		if (!(this->kmsKeyId.IsEmpty())) {
            awsCreateLogGroupRequest.SetKmsKeyId(TCHAR_TO_UTF8(*this->kmsKeyId));
        }

        for (const TPair<FString, FString>& elem : this->tags) {
            awsCreateLogGroupRequest.AddTags(TCHAR_TO_UTF8(*elem.Key), TCHAR_TO_UTF8(*elem.Value));
        }

        return awsCreateLogGroupRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty() && this->kmsKeyId.IsEmpty() && this->tags.Num() == 0;
    }
#endif
};

/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/PutDestinationRequest.h"

#endif

#include "PutDestinationRequest.generated.h"

USTRUCT(BlueprintType)
struct FPutDestinationRequest {
GENERATED_BODY()

    /**
    *  <p>A name for the destination.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString destinationName;

    /**
    *  <p>The ARN of an Amazon Kinesis stream to which to deliver matching log events.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString targetArn;

    /**
    *  <p>The ARN of an IAM role that grants CloudWatch Logs permissions to call the Amazon Kinesis <code>PutRecord</code> operation on the destination stream.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString roleArn;

    /**
    *  <p>An optional list of key-value pairs to associate with the resource.</p> <p>For more information about tagging, see <a href="https://docs.aws.amazon.com/general/latest/gr/aws_tagging.html">Tagging Amazon Web Services resources</a> </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TMap<FString, FString> tags;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::PutDestinationRequest toAWS() const {
        Aws::CloudWatchLogs::Model::PutDestinationRequest awsPutDestinationRequest;

		if (!(this->destinationName.IsEmpty())) {
            awsPutDestinationRequest.SetDestinationName(TCHAR_TO_UTF8(*this->destinationName));
        }

		if (!(this->targetArn.IsEmpty())) {
            awsPutDestinationRequest.SetTargetArn(TCHAR_TO_UTF8(*this->targetArn));
        }

		if (!(this->roleArn.IsEmpty())) {
            awsPutDestinationRequest.SetRoleArn(TCHAR_TO_UTF8(*this->roleArn));
        }

        for (const TPair<FString, FString>& elem : this->tags) {
            awsPutDestinationRequest.AddTags(TCHAR_TO_UTF8(*elem.Key), TCHAR_TO_UTF8(*elem.Value));
        }

        return awsPutDestinationRequest;
    }

    bool IsEmpty() const {
        return this->destinationName.IsEmpty() && this->targetArn.IsEmpty() && this->roleArn.IsEmpty() && this->tags.Num() == 0;
    }
#endif
};

/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, December 2022
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/UntagResourceRequest.h"

#endif

#include "AWSCloudWatchLogsUntagResourceRequest.generated.h"

USTRUCT(BlueprintType)
struct FAWSCloudWatchLogsUntagResourceRequest {
GENERATED_BODY()

    /**
    *  <p>The ARN of the CloudWatch Logs resource that you're removing tags from.</p> <p>The ARN format of a log group is <code>arn:aws:logs:<i>Region</i>:<i>account-id</i>:log-group:<i>log-group-name</i> </code> </p> <p>The ARN format of a destination is <code>arn:aws:logs:<i>Region</i>:<i>account-id</i>:destination:<i>destination-name</i> </code> </p> <p>For more information about ARN format, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/logs/iam-access-control-overview-cwl.html">CloudWatch Logs resources and operations</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString resourceArn;

    /**
    *  <p>The list of tag keys to remove from the resource.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FString> tagKeys;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::UntagResourceRequest toAWS() const {
        Aws::CloudWatchLogs::Model::UntagResourceRequest awsUntagResourceRequest;

        if (!(this->resourceArn.IsEmpty())) {
            awsUntagResourceRequest.SetResourceArn(TCHAR_TO_UTF8(*this->resourceArn));
        }

        for (const FString& elem : this->tagKeys) {
            awsUntagResourceRequest.AddTagKeys(TCHAR_TO_UTF8(*elem));
        }

        return awsUntagResourceRequest;
    }

    bool IsEmpty() const {
        return this->resourceArn.IsEmpty() && this->tagKeys.Num() == 0;
    }
#endif
};

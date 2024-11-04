/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, December 2022
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/TagResourceRequest.h"

#endif

#include "AWSCloudWatchLogsTagResourceRequest.generated.h"

USTRUCT(BlueprintType)
struct FAWSCloudWatchLogsTagResourceRequest {
GENERATED_BODY()

    /**
    *  <p>The ARN of the resource that you're adding tags to.</p> <p>The ARN format of a log group is <code>arn:aws:logs:<i>Region</i>:<i>account-id</i>:log-group:<i>log-group-name</i> </code> </p> <p>The ARN format of a destination is <code>arn:aws:logs:<i>Region</i>:<i>account-id</i>:destination:<i>destination-name</i> </code> </p> <p>For more information about ARN format, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/logs/iam-access-control-overview-cwl.html">CloudWatch Logs resources and operations</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString resourceArn;
    /**
    *  <p>The list of key-value pairs to associate with the resource.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TMap<FString, FString> tags;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::TagResourceRequest toAWS() const {
        Aws::CloudWatchLogs::Model::TagResourceRequest awsTagResourceRequest;

        if (!(this->resourceArn.IsEmpty())) {
            awsTagResourceRequest.SetResourceArn(TCHAR_TO_UTF8(*this->resourceArn));
        }

        for (const TPair<FString, FString>& elem : this->tags) {
            awsTagResourceRequest.AddTags(TCHAR_TO_UTF8(*elem.Key), TCHAR_TO_UTF8(*elem.Value));
        }

        return awsTagResourceRequest;
    }

    bool IsEmpty() const {
        return this->resourceArn.IsEmpty() && this->tags.Num() == 0 && true;
    }
#endif
};

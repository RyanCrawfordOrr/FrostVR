/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, January 2023
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/ListTagsForResourceRequest.h"

#endif

#include "AWSCloudWatchLogsListTagsForResourceRequest.generated.h"

USTRUCT(BlueprintType)
struct FAWSCloudWatchLogsListTagsForResourceRequest {
GENERATED_BODY()

    /**
    *  <p>The ARN of the resource that you want to view tags for.</p> <p>The ARN format of a log group is <code>arn:aws:logs:<i>Region</i>:<i>account-id</i>:log-group:<i>log-group-name</i> </code> </p> <p>The ARN format of a destination is <code>arn:aws:logs:<i>Region</i>:<i>account-id</i>:destination:<i>destination-name</i> </code> </p> <p>For more information about ARN format, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/logs/iam-access-control-overview-cwl.html">CloudWatch Logs resources and operations</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString resourceArn;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::ListTagsForResourceRequest toAWS() const {
        Aws::CloudWatchLogs::Model::ListTagsForResourceRequest awsListTagsForResourceRequest;

		if (!(this->resourceArn.IsEmpty())) {
            awsListTagsForResourceRequest.SetResourceArn(TCHAR_TO_UTF8(*this->resourceArn));
        }

        return awsListTagsForResourceRequest;
    }

    bool IsEmpty() const {
        return this->resourceArn.IsEmpty();
    }
#endif
};

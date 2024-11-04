/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/PutSubscriptionFilterRequest.h"

#endif

#include "Model/AWSDistribution.h"

#include "PutSubscriptionFilterRequest.generated.h"

USTRUCT(BlueprintType)
struct FPutSubscriptionFilterRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    *  <p>A name for the subscription filter. If you are updating an existing filter, you must specify the correct name in <code>filterName</code>. Otherwise, the call fails because you cannot associate a second filter with a log group. To find the name of the filter currently associated with a log group, use <a href="https://docs.aws.amazon.com/AmazonCloudWatchLogs/latest/APIReference/API_DescribeSubscriptionFilters.html">DescribeSubscriptionFilters</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString filterName;

    /**
    *  <p>A filter pattern for subscribing to a filtered stream of log events.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString filterPattern;

    /**
    *  <p>The ARN of the destination to deliver matching log events to. Currently, the supported destinations are:</p> <ul> <li> <p>An Amazon Kinesis stream belonging to the same account as the subscription filter, for same-account delivery.</p> </li> <li> <p>A logical destination (specified using an ARN) belonging to a different account, for cross-account delivery.</p> </li> <li> <p>An Amazon Kinesis Firehose delivery stream belonging to the same account as the subscription filter, for same-account delivery.</p> </li> <li> <p>An AWS Lambda function belonging to the same account as the subscription filter, for same-account delivery.</p> </li> </ul>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString destinationArn;

    /**
    *  <p>The ARN of an IAM role that grants CloudWatch Logs permissions to deliver ingested log events to the destination stream. You don't need to provide the ARN when you are working with a logical destination for cross-account delivery.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString roleArn;

    /**
    *  <p>The method used to distribute log data to the destination. By default, log data is grouped by log stream, but the grouping can be set to random for a more even distribution. This property is only applicable when the destination is an Amazon Kinesis stream. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    EAWSDistribution distribution = EAWSDistribution::NOT_SET;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::PutSubscriptionFilterRequest toAWS() const {
        Aws::CloudWatchLogs::Model::PutSubscriptionFilterRequest awsPutSubscriptionFilterRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsPutSubscriptionFilterRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

		if (!(this->filterName.IsEmpty())) {
            awsPutSubscriptionFilterRequest.SetFilterName(TCHAR_TO_UTF8(*this->filterName));
        }

		if (!(this->filterPattern.IsEmpty())) {
            awsPutSubscriptionFilterRequest.SetFilterPattern(TCHAR_TO_UTF8(*this->filterPattern));
        }

		if (!(this->destinationArn.IsEmpty())) {
            awsPutSubscriptionFilterRequest.SetDestinationArn(TCHAR_TO_UTF8(*this->destinationArn));
        }

		if (!(this->roleArn.IsEmpty())) {
            awsPutSubscriptionFilterRequest.SetRoleArn(TCHAR_TO_UTF8(*this->roleArn));
        }

        switch(this->distribution) {
            case EAWSDistribution::Random:
                awsPutSubscriptionFilterRequest.SetDistribution(Aws::CloudWatchLogs::Model::Distribution::Random);
                break;
            case EAWSDistribution::ByLogStream:
                awsPutSubscriptionFilterRequest.SetDistribution(Aws::CloudWatchLogs::Model::Distribution::ByLogStream);
                break;
            default:
                break;
		}

        return awsPutSubscriptionFilterRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty() && this->filterName.IsEmpty() && this->filterPattern.IsEmpty() && this->destinationArn.IsEmpty() && this->roleArn.IsEmpty() && distribution == EAWSDistribution::NOT_SET;
    }
#endif
};

/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/SubscriptionFilter.h"

#endif

#include "Model/AWSDistribution.h"

#include "SubscriptionFilter.generated.h"

USTRUCT(BlueprintType)
struct FSubscriptionFilter {
GENERATED_BODY()

    /**
    *  <p>The name of the subscription filter.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString filterName;

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString filterPattern;

    /**
    *  <p>The Amazon Resource Name (ARN) of the destination.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString destinationArn;

    /**
    *  <p/>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString roleArn;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    EAWSDistribution distribution = EAWSDistribution::NOT_SET;

    /**
    *  <p>The creation time of the subscription filter, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 creationTime = 0;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FSubscriptionFilter &fromAWS(const Aws::CloudWatchLogs::Model::SubscriptionFilter &awsSubscriptionFilter) {
        this->filterName = UTF8_TO_TCHAR(awsSubscriptionFilter.GetFilterName().c_str());

        this->logGroupName = UTF8_TO_TCHAR(awsSubscriptionFilter.GetLogGroupName().c_str());

        this->filterPattern = UTF8_TO_TCHAR(awsSubscriptionFilter.GetFilterPattern().c_str());

        this->destinationArn = UTF8_TO_TCHAR(awsSubscriptionFilter.GetDestinationArn().c_str());

        this->roleArn = UTF8_TO_TCHAR(awsSubscriptionFilter.GetRoleArn().c_str());

        switch(awsSubscriptionFilter.GetDistribution()) {
            case Aws::CloudWatchLogs::Model::Distribution::NOT_SET:
                this->distribution = EAWSDistribution::NOT_SET;
                break;
            case Aws::CloudWatchLogs::Model::Distribution::Random:
                this->distribution = EAWSDistribution::Random;
                break;
            case Aws::CloudWatchLogs::Model::Distribution::ByLogStream:
                this->distribution = EAWSDistribution::ByLogStream;
                break;
            default:
                this->distribution = EAWSDistribution::NOT_SET;
                break;
        }

        this->creationTime = (int64)awsSubscriptionFilter.GetCreationTime();

        return *this;
    }
#endif
};

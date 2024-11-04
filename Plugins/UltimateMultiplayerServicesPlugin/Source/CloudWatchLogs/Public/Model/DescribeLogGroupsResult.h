/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DescribeLogGroupsResult.h"

#endif

#include "Model/LogGroup.h"

#include "DescribeLogGroupsResult.generated.h"

USTRUCT(BlueprintType)
struct FDescribeLogGroupsResult {
GENERATED_BODY()

    /**
    *  <p>The log groups.</p> <p>If the <code>retentionInDays</code> value if not included for a log group, then that log group is set to have its events never expire.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FLogGroup> logGroups;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextToken;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FDescribeLogGroupsResult &fromAWS(const Aws::CloudWatchLogs::Model::DescribeLogGroupsResult &awsDescribeLogGroupsResult) {
        this->logGroups.Empty();
        for (const Aws::CloudWatchLogs::Model::LogGroup& elem : awsDescribeLogGroupsResult.GetLogGroups()) {
            this->logGroups.Add(FLogGroup().fromAWS(elem));
        }

        this->nextToken = UTF8_TO_TCHAR(awsDescribeLogGroupsResult.GetNextToken().c_str());

        return *this;
    }
#endif
};

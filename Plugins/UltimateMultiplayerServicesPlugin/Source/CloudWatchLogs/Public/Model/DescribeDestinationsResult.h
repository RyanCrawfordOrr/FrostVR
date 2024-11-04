/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DescribeDestinationsResult.h"

#endif

#include "Model/CloudWatchLogsDestination.h"

#include "DescribeDestinationsResult.generated.h"

USTRUCT(BlueprintType)
struct FDescribeDestinationsResult {
GENERATED_BODY()

    /**
    *  <p>The destinations.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FCloudWatchLogsDestination> destinations;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextToken;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FDescribeDestinationsResult &fromAWS(const Aws::CloudWatchLogs::Model::DescribeDestinationsResult &awsDescribeDestinationsResult) {
        this->destinations.Empty();
        for (const Aws::CloudWatchLogs::Model::Destination& elem : awsDescribeDestinationsResult.GetDestinations()) {
            this->destinations.Add(FCloudWatchLogsDestination().fromAWS(elem));
        }

        this->nextToken = UTF8_TO_TCHAR(awsDescribeDestinationsResult.GetNextToken().c_str());

        return *this;
    }
#endif
};

/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/QueryStatistics.h"

#endif

#include "QueryStatistics.generated.h"

USTRUCT(BlueprintType)
struct FQueryStatistics {
GENERATED_BODY()

    /**
    *  <p>The number of log events that matched the query string.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    float recordsMatched = 0.0f;

    /**
    *  <p>The total number of log events scanned during the query.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    float recordsScanned = 0.0f;

    /**
    *  <p>The total number of bytes in the log events scanned during the query.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    float bytesScanned = 0.0f;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FQueryStatistics &fromAWS(const Aws::CloudWatchLogs::Model::QueryStatistics &awsQueryStatistics) {
        this->recordsMatched = (float)awsQueryStatistics.GetRecordsMatched();

        this->recordsScanned = (float)awsQueryStatistics.GetRecordsScanned();

        this->bytesScanned = (float)awsQueryStatistics.GetBytesScanned();

        return *this;
    }
#endif
};

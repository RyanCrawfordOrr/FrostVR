/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/TestMetricFilterResult.h"

#endif

#include "Model/MetricFilterMatchRecord.h"

#include "TestMetricFilterResult.generated.h"

USTRUCT(BlueprintType)
struct FTestMetricFilterResult {
GENERATED_BODY()

    /**
    *  <p>The matched events.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FMetricFilterMatchRecord> matches;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FTestMetricFilterResult &fromAWS(const Aws::CloudWatchLogs::Model::TestMetricFilterResult &awsTestMetricFilterResult) {
        this->matches.Empty();
        for (const Aws::CloudWatchLogs::Model::MetricFilterMatchRecord& elem : awsTestMetricFilterResult.GetMatches()) {
            this->matches.Add(FMetricFilterMatchRecord().fromAWS(elem));
        }

        return *this;
    }
#endif
};

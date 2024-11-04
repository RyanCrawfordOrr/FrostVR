/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/StopQueryResult.h"

#endif

#include "StopQueryResult.generated.h"

USTRUCT(BlueprintType)
struct FStopQueryResult {
GENERATED_BODY()

    /**
    *  <p>This is true if the query was stopped by the <code>StopQuery</code> operation.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    bool success = false;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FStopQueryResult &fromAWS(const Aws::CloudWatchLogs::Model::StopQueryResult &awsStopQueryResult) {
        this->success = awsStopQueryResult.GetSuccess();

        return *this;
    }
#endif
};

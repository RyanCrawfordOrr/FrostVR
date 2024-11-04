/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/StartQueryResult.h"

#endif

#include "StartQueryResult.generated.h"

USTRUCT(BlueprintType)
struct FStartQueryResult {
GENERATED_BODY()

    /**
    *  <p>The unique ID of the query. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString queryId;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FStartQueryResult &fromAWS(const Aws::CloudWatchLogs::Model::StartQueryResult &awsStartQueryResult) {
        this->queryId = UTF8_TO_TCHAR(awsStartQueryResult.GetQueryId().c_str());

        return *this;
    }
#endif
};

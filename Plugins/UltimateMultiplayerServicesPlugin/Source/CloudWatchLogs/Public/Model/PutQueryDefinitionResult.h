/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/PutQueryDefinitionResult.h"

#endif

#include "PutQueryDefinitionResult.generated.h"

USTRUCT(BlueprintType)
struct FPutQueryDefinitionResult {
GENERATED_BODY()

    /**
    *  <p>The ID of the query definition.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString queryDefinitionId;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FPutQueryDefinitionResult &fromAWS(const Aws::CloudWatchLogs::Model::PutQueryDefinitionResult &awsPutQueryDefinitionResult) {
        this->queryDefinitionId = UTF8_TO_TCHAR(awsPutQueryDefinitionResult.GetQueryDefinitionId().c_str());

        return *this;
    }
#endif
};

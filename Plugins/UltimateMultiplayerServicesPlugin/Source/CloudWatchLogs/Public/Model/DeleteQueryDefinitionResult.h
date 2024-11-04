/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DeleteQueryDefinitionResult.h"

#endif

#include "DeleteQueryDefinitionResult.generated.h"

USTRUCT(BlueprintType)
struct FDeleteQueryDefinitionResult {
GENERATED_BODY()

    /**
    *  <p>A value of TRUE indicates that the operation succeeded. FALSE indicates that the operation failed.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    bool success = false;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FDeleteQueryDefinitionResult &fromAWS(const Aws::CloudWatchLogs::Model::DeleteQueryDefinitionResult &awsDeleteQueryDefinitionResult) {
        this->success = awsDeleteQueryDefinitionResult.GetSuccess();

        return *this;
    }
#endif
};

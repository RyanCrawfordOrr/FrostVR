/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/PutResourcePolicyResult.h"

#endif

#include "Model/ResourcePolicy.h"

#include "PutResourcePolicyResult.generated.h"

USTRUCT(BlueprintType)
struct FPutResourcePolicyResult {
GENERATED_BODY()

    /**
    *  <p>The new policy.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FResourcePolicy resourcePolicy;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FPutResourcePolicyResult &fromAWS(const Aws::CloudWatchLogs::Model::PutResourcePolicyResult &awsPutResourcePolicyResult) {
        this->resourcePolicy.fromAWS(awsPutResourcePolicyResult.GetResourcePolicy());

        return *this;
    }
#endif
};

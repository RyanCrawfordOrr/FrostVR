/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/PutLogEventsResult.h"

#endif

#include "Model/RejectedLogEventsInfo.h"

#include "PutLogEventsResult.generated.h"

USTRUCT(BlueprintType)
struct FPutLogEventsResult {
GENERATED_BODY()

    /**
    *  <p>The next sequence token.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextSequenceToken;

    /**
    *  <p>The rejected events.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FRejectedLogEventsInfo rejectedLogEventsInfo;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FPutLogEventsResult &fromAWS(const Aws::CloudWatchLogs::Model::PutLogEventsResult &awsPutLogEventsResult) {
        this->nextSequenceToken = UTF8_TO_TCHAR(awsPutLogEventsResult.GetNextSequenceToken().c_str());

        this->rejectedLogEventsInfo.fromAWS(awsPutLogEventsResult.GetRejectedLogEventsInfo());

        return *this;
    }
#endif
};

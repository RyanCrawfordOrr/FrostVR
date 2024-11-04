/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/RejectedLogEventsInfo.h"

#endif

#include "RejectedLogEventsInfo.generated.h"

USTRUCT(BlueprintType)
struct FRejectedLogEventsInfo {
GENERATED_BODY()

    /**
    *  <p>The log events that are too new.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int tooNewLogEventStartIndex = 0;

    /**
    *  <p>The log events that are too old.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int tooOldLogEventEndIndex = 0;

    /**
    *  <p>The expired log events.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int expiredLogEventEndIndex = 0;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FRejectedLogEventsInfo &fromAWS(const Aws::CloudWatchLogs::Model::RejectedLogEventsInfo &awsRejectedLogEventsInfo) {
		this->tooNewLogEventStartIndex = awsRejectedLogEventsInfo.GetTooNewLogEventStartIndex();

		this->tooOldLogEventEndIndex = awsRejectedLogEventsInfo.GetTooOldLogEventEndIndex();

		this->expiredLogEventEndIndex = awsRejectedLogEventsInfo.GetExpiredLogEventEndIndex();

        return *this;
    }
#endif
};

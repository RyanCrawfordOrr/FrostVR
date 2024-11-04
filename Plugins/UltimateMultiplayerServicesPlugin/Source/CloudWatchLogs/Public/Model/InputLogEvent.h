/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/InputLogEvent.h"

#endif

#include "InputLogEvent.generated.h"

USTRUCT(BlueprintType)
struct FInputLogEvent {
GENERATED_BODY()

    /**
    *  <p>The time the event occurred, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 timestamp = 0;

    /**
    *  <p>The raw event message.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString message;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::InputLogEvent toAWS() const {
        Aws::CloudWatchLogs::Model::InputLogEvent awsInputLogEvent;

        if (!(this->timestamp == 0)) {
            awsInputLogEvent.SetTimestamp(this->timestamp);
        }

		if (!(this->message.IsEmpty())) {
            awsInputLogEvent.SetMessage(TCHAR_TO_UTF8(*this->message));
        }

        return awsInputLogEvent;
    }

    bool IsEmpty() const {
        return this->timestamp == 0 && this->message.IsEmpty();
    }
#endif
};

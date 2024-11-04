/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/GetLogEventsResult.h"

#endif

#include "Model/OutputLogEvent.h"

#include "GetLogEventsResult.generated.h"

USTRUCT(BlueprintType)
struct FGetLogEventsResult {
GENERATED_BODY()

    /**
    *  <p>The events.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FOutputLogEvent> events;

    /**
    *  <p>The token for the next set of items in the forward direction. The token expires after 24 hours. If you have reached the end of the stream, it returns the same token you passed in.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextForwardToken;

    /**
    *  <p>The token for the next set of items in the backward direction. The token expires after 24 hours. This token is never null. If you have reached the end of the stream, it returns the same token you passed in.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextBackwardToken;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FGetLogEventsResult &fromAWS(const Aws::CloudWatchLogs::Model::GetLogEventsResult &awsGetLogEventsResult) {
        this->events.Empty();
        for (const Aws::CloudWatchLogs::Model::OutputLogEvent& elem : awsGetLogEventsResult.GetEvents()) {
            this->events.Add(FOutputLogEvent().fromAWS(elem));
        }

        this->nextForwardToken = UTF8_TO_TCHAR(awsGetLogEventsResult.GetNextForwardToken().c_str());

        this->nextBackwardToken = UTF8_TO_TCHAR(awsGetLogEventsResult.GetNextBackwardToken().c_str());

        return *this;
    }
#endif
};

/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/FilterLogEventsResult.h"

#endif

#include "Model/FilteredLogEvent.h"
#include "Model/SearchedLogStream.h"

#include "FilterLogEventsResult.generated.h"

USTRUCT(BlueprintType)
struct FFilterLogEventsResult {
GENERATED_BODY()

    /**
    *  <p>The matched events.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FFilteredLogEvent> events;

    /**
    *  <p> <b>IMPORTANT</b> Starting on May 15, 2020, this parameter will be deprecated. This parameter will be an empty list after the deprecation occurs.</p> <p>Indicates which log streams have been searched and whether each has been searched completely.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FSearchedLogStream> searchedLogStreams;

    /**
    *  <p>The token to use when requesting the next set of items. The token expires after 24 hours.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextToken;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FFilterLogEventsResult &fromAWS(const Aws::CloudWatchLogs::Model::FilterLogEventsResult &awsFilterLogEventsResult) {
        this->events.Empty();
        for (const Aws::CloudWatchLogs::Model::FilteredLogEvent& elem : awsFilterLogEventsResult.GetEvents()) {
            this->events.Add(FFilteredLogEvent().fromAWS(elem));
        }

        this->searchedLogStreams.Empty();
        for (const Aws::CloudWatchLogs::Model::SearchedLogStream& elem : awsFilterLogEventsResult.GetSearchedLogStreams()) {
            this->searchedLogStreams.Add(FSearchedLogStream().fromAWS(elem));
        }

        this->nextToken = UTF8_TO_TCHAR(awsFilterLogEventsResult.GetNextToken().c_str());

        return *this;
    }
#endif
};

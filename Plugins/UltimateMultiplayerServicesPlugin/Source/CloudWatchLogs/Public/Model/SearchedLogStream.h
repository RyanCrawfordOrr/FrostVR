/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/SearchedLogStream.h"

#endif

#include "SearchedLogStream.generated.h"

USTRUCT(BlueprintType)
struct FSearchedLogStream {
GENERATED_BODY()

    /**
    *  <p>The name of the log stream.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logStreamName;

    /**
    *  <p>Indicates whether all the events in this log stream were searched.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    bool searchedCompletely = false;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FSearchedLogStream &fromAWS(const Aws::CloudWatchLogs::Model::SearchedLogStream &awsSearchedLogStream) {
        this->logStreamName = UTF8_TO_TCHAR(awsSearchedLogStream.GetLogStreamName().c_str());

        this->searchedCompletely = awsSearchedLogStream.GetSearchedCompletely();

        return *this;
    }
#endif
};

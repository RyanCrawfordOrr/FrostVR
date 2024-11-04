/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/GetQueryResultsRequest.h"

#endif

#include "GetQueryResultsRequest.generated.h"

USTRUCT(BlueprintType)
struct FGetQueryResultsRequest {
GENERATED_BODY()

    /**
    *  <p>The ID number of the query.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString queryId;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::GetQueryResultsRequest toAWS() const {
        Aws::CloudWatchLogs::Model::GetQueryResultsRequest awsGetQueryResultsRequest;

		if (!(this->queryId.IsEmpty())) {
            awsGetQueryResultsRequest.SetQueryId(TCHAR_TO_UTF8(*this->queryId));
        }

        return awsGetQueryResultsRequest;
    }

    bool IsEmpty() const {
        return this->queryId.IsEmpty();
    }
#endif
};

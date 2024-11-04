/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/StopQueryRequest.h"

#endif

#include "StopQueryRequest.generated.h"

USTRUCT(BlueprintType)
struct FStopQueryRequest {
GENERATED_BODY()

    /**
    *  <p>The ID number of the query to stop. To find this ID number, use <code>DescribeQueries</code>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString queryId;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::StopQueryRequest toAWS() const {
        Aws::CloudWatchLogs::Model::StopQueryRequest awsStopQueryRequest;

		if (!(this->queryId.IsEmpty())) {
            awsStopQueryRequest.SetQueryId(TCHAR_TO_UTF8(*this->queryId));
        }

        return awsStopQueryRequest;
    }

    bool IsEmpty() const {
        return this->queryId.IsEmpty();
    }
#endif
};

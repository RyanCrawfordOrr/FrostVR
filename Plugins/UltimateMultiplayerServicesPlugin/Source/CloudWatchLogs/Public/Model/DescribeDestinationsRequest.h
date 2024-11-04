/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DescribeDestinationsRequest.h"

#endif

#include "DescribeDestinationsRequest.generated.h"

USTRUCT(BlueprintType)
struct FDescribeDestinationsRequest {
GENERATED_BODY()

    /**
    *  <p>The prefix to match. If you don't specify a value, no prefix filter is applied.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString destinationNamePrefix;

    /**
    *  <p>The token for the next set of items to return. (You received this token from a previous call.)</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextToken;

    /**
    *  <p>The maximum number of items returned. If you don't specify a value, the default is up to 50 items.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int limit = 0;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::DescribeDestinationsRequest toAWS() const {
        Aws::CloudWatchLogs::Model::DescribeDestinationsRequest awsDescribeDestinationsRequest;

		if (!(this->destinationNamePrefix.IsEmpty())) {
            awsDescribeDestinationsRequest.SetDestinationNamePrefix(TCHAR_TO_UTF8(*this->destinationNamePrefix));
        }

		if (!(this->nextToken.IsEmpty())) {
            awsDescribeDestinationsRequest.SetNextToken(TCHAR_TO_UTF8(*this->nextToken));
        }

        if (!(this->limit == 0)) {
            awsDescribeDestinationsRequest.SetLimit(this->limit);
        }

        return awsDescribeDestinationsRequest;
    }

    bool IsEmpty() const {
        return this->destinationNamePrefix.IsEmpty() && this->nextToken.IsEmpty() && this->limit == 0;
    }
#endif
};

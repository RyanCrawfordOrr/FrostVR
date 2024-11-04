/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DescribeResourcePoliciesRequest.h"

#endif

#include "DescribeResourcePoliciesRequest.generated.h"

USTRUCT(BlueprintType)
struct FDescribeResourcePoliciesRequest {
GENERATED_BODY()

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextToken;

    /**
    *  <p>The maximum number of resource policies to be displayed with one call of this API.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int limit = 0;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::DescribeResourcePoliciesRequest toAWS() const {
        Aws::CloudWatchLogs::Model::DescribeResourcePoliciesRequest awsDescribeResourcePoliciesRequest;

		if (!(this->nextToken.IsEmpty())) {
            awsDescribeResourcePoliciesRequest.SetNextToken(TCHAR_TO_UTF8(*this->nextToken));
        }

        if (!(this->limit == 0)) {
            awsDescribeResourcePoliciesRequest.SetLimit(this->limit);
        }

        return awsDescribeResourcePoliciesRequest;
    }

    bool IsEmpty() const {
        return this->nextToken.IsEmpty() && this->limit == 0;
    }
#endif
};

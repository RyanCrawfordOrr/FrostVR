/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DescribeResourcePoliciesResult.h"

#endif

#include "Model/ResourcePolicy.h"

#include "DescribeResourcePoliciesResult.generated.h"

USTRUCT(BlueprintType)
struct FDescribeResourcePoliciesResult {
GENERATED_BODY()

    /**
    *  <p>The resource policies that exist in this account.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FResourcePolicy> resourcePolicies;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextToken;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FDescribeResourcePoliciesResult &fromAWS(const Aws::CloudWatchLogs::Model::DescribeResourcePoliciesResult &awsDescribeResourcePoliciesResult) {
        this->resourcePolicies.Empty();
        for (const Aws::CloudWatchLogs::Model::ResourcePolicy& elem : awsDescribeResourcePoliciesResult.GetResourcePolicies()) {
            this->resourcePolicies.Add(FResourcePolicy().fromAWS(elem));
        }

        this->nextToken = UTF8_TO_TCHAR(awsDescribeResourcePoliciesResult.GetNextToken().c_str());

        return *this;
    }
#endif
};

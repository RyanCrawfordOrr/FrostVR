/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DescribeQueryDefinitionsRequest.h"

#endif

#include "DescribeQueryDefinitionsRequest.generated.h"

USTRUCT(BlueprintType)
struct FDescribeQueryDefinitionsRequest {
GENERATED_BODY()

    /**
    *  <p>Use this parameter to filter your results to only the query definitions that have names that start with the prefix you specify.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString queryDefinitionNamePrefix;

    /**
    *  <p>Limits the number of returned query definitions to the specified number.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int maxResults = 0;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextToken;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::DescribeQueryDefinitionsRequest toAWS() const {
        Aws::CloudWatchLogs::Model::DescribeQueryDefinitionsRequest awsDescribeQueryDefinitionsRequest;

		if (!(this->queryDefinitionNamePrefix.IsEmpty())) {
            awsDescribeQueryDefinitionsRequest.SetQueryDefinitionNamePrefix(TCHAR_TO_UTF8(*this->queryDefinitionNamePrefix));
        }

        if (!(this->maxResults == 0)) {
            awsDescribeQueryDefinitionsRequest.SetMaxResults(this->maxResults);
        }

		if (!(this->nextToken.IsEmpty())) {
            awsDescribeQueryDefinitionsRequest.SetNextToken(TCHAR_TO_UTF8(*this->nextToken));
        }

        return awsDescribeQueryDefinitionsRequest;
    }

    bool IsEmpty() const {
        return this->queryDefinitionNamePrefix.IsEmpty() && this->maxResults == 0 && this->nextToken.IsEmpty();
    }
#endif
};

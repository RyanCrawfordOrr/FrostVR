/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DescribeQueryDefinitionsResult.h"

#endif

#include "Model/QueryDefinition.h"

#include "DescribeQueryDefinitionsResult.generated.h"

USTRUCT(BlueprintType)
struct FDescribeQueryDefinitionsResult {
GENERATED_BODY()

    /**
    *  <p>The list of query definitions that match your request.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FQueryDefinition> queryDefinitions;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextToken;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FDescribeQueryDefinitionsResult &fromAWS(const Aws::CloudWatchLogs::Model::DescribeQueryDefinitionsResult &awsDescribeQueryDefinitionsResult) {
        this->queryDefinitions.Empty();
        for (const Aws::CloudWatchLogs::Model::QueryDefinition& elem : awsDescribeQueryDefinitionsResult.GetQueryDefinitions()) {
            this->queryDefinitions.Add(FQueryDefinition().fromAWS(elem));
        }

        this->nextToken = UTF8_TO_TCHAR(awsDescribeQueryDefinitionsResult.GetNextToken().c_str());

        return *this;
    }
#endif
};

/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DescribeQueriesResult.h"

#endif

#include "Model/QueryInfo.h"

#include "DescribeQueriesResult.generated.h"

USTRUCT(BlueprintType)
struct FDescribeQueriesResult {
GENERATED_BODY()

    /**
    *  <p>The list of queries that match the request.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FQueryInfo> queries;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextToken;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FDescribeQueriesResult &fromAWS(const Aws::CloudWatchLogs::Model::DescribeQueriesResult &awsDescribeQueriesResult) {
        this->queries.Empty();
        for (const Aws::CloudWatchLogs::Model::QueryInfo& elem : awsDescribeQueriesResult.GetQueries()) {
            this->queries.Add(FQueryInfo().fromAWS(elem));
        }

        this->nextToken = UTF8_TO_TCHAR(awsDescribeQueriesResult.GetNextToken().c_str());

        return *this;
    }
#endif
};

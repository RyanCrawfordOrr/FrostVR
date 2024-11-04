/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/PutQueryDefinitionRequest.h"

#endif

#include "PutQueryDefinitionRequest.generated.h"

USTRUCT(BlueprintType)
struct FPutQueryDefinitionRequest {
GENERATED_BODY()

    /**
    *  <p>A name for the query definition. If you are saving a lot of query definitions, we recommend that you name them so that you can easily find the ones you want by using the first part of the name as a filter in the <code>queryDefinitionNamePrefix</code> parameter of <a href="https://docs.aws.amazon.com/AmazonCloudWatchLogs/latest/APIReference/API_DescribeQueryDefinitions.html">DescribeQueryDefinitions</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString name;

    /**
    *  <p>If you are updating a query definition, use this parameter to specify the ID of the query definition that you want to update. You can use <a href="https://docs.aws.amazon.com/AmazonCloudWatchLogs/latest/APIReference/API_DescribeQueryDefinitions.html">DescribeQueryDefinitions</a> to retrieve the IDs of your saved query definitions.</p> <p>If you are creating a query definition, do not specify this parameter. CloudWatch generates a unique ID for the new query definition and include it in the response to this operation.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString queryDefinitionId;

    /**
    *  <p>Use this parameter to include specific log groups as part of your query definition.</p> <p>If you are updating a query definition and you omit this parameter, then the updated definition will contain no log groups.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FString> logGroupNames;

    /**
    *  <p>The query string to use for this definition. For more information, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/logs/CWL_QuerySyntax.html">CloudWatch Logs Insights Query Syntax</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString queryString;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::PutQueryDefinitionRequest toAWS() const {
        Aws::CloudWatchLogs::Model::PutQueryDefinitionRequest awsPutQueryDefinitionRequest;

		if (!(this->name.IsEmpty())) {
            awsPutQueryDefinitionRequest.SetName(TCHAR_TO_UTF8(*this->name));
        }

		if (!(this->queryDefinitionId.IsEmpty())) {
            awsPutQueryDefinitionRequest.SetQueryDefinitionId(TCHAR_TO_UTF8(*this->queryDefinitionId));
        }

        for (const FString& elem : this->logGroupNames) {
            awsPutQueryDefinitionRequest.AddLogGroupNames(TCHAR_TO_UTF8(*elem));
        }

		if (!(this->queryString.IsEmpty())) {
            awsPutQueryDefinitionRequest.SetQueryString(TCHAR_TO_UTF8(*this->queryString));
        }

        return awsPutQueryDefinitionRequest;
    }

    bool IsEmpty() const {
        return this->name.IsEmpty() && this->queryDefinitionId.IsEmpty() && this->logGroupNames.Num() == 0 && this->queryString.IsEmpty();
    }
#endif
};

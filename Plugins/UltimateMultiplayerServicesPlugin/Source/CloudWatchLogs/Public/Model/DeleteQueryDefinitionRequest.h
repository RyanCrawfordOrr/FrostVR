/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DeleteQueryDefinitionRequest.h"

#endif

#include "DeleteQueryDefinitionRequest.generated.h"

USTRUCT(BlueprintType)
struct FDeleteQueryDefinitionRequest {
GENERATED_BODY()

    /**
    *  <p>The ID of the query definition that you want to delete. You can use <a href="https://docs.aws.amazon.com/AmazonCloudWatchLogs/latest/APIReference/API_DescribeQueryDefinitions.html">DescribeQueryDefinitions</a> to retrieve the IDs of your saved query definitions.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString queryDefinitionId;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::DeleteQueryDefinitionRequest toAWS() const {
        Aws::CloudWatchLogs::Model::DeleteQueryDefinitionRequest awsDeleteQueryDefinitionRequest;

		if (!(this->queryDefinitionId.IsEmpty())) {
            awsDeleteQueryDefinitionRequest.SetQueryDefinitionId(TCHAR_TO_UTF8(*this->queryDefinitionId));
        }

        return awsDeleteQueryDefinitionRequest;
    }

    bool IsEmpty() const {
        return this->queryDefinitionId.IsEmpty();
    }
#endif
};

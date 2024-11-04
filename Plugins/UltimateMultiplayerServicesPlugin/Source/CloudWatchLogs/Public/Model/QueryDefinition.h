/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/QueryDefinition.h"

#endif

#include "QueryDefinition.generated.h"

USTRUCT(BlueprintType)
struct FQueryDefinition {
GENERATED_BODY()

    /**
    *  <p>The unique ID of the query definition.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString queryDefinitionId;

    /**
    *  <p>The name of the query definition.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString name;

    /**
    *  <p>The query string to use for this definition. For more information, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/logs/CWL_QuerySyntax.html">CloudWatch Logs Insights Query Syntax</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString queryString;

    /**
    *  <p>The date that the query definition was most recently modified.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 lastModified = 0;

    /**
    *  <p>If this query definition contains a list of log groups that it is limited to, that list appears here.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FString> logGroupNames;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FQueryDefinition &fromAWS(const Aws::CloudWatchLogs::Model::QueryDefinition &awsQueryDefinition) {
        this->queryDefinitionId = UTF8_TO_TCHAR(awsQueryDefinition.GetQueryDefinitionId().c_str());

        this->name = UTF8_TO_TCHAR(awsQueryDefinition.GetName().c_str());

        this->queryString = UTF8_TO_TCHAR(awsQueryDefinition.GetQueryString().c_str());

        this->lastModified = (int64)awsQueryDefinition.GetLastModified();

        this->logGroupNames.Empty();
        for (const Aws::String& elem : awsQueryDefinition.GetLogGroupNames()) {
            this->logGroupNames.Add(UTF8_TO_TCHAR(elem.c_str()));
        }

        return *this;
    }
#endif
};

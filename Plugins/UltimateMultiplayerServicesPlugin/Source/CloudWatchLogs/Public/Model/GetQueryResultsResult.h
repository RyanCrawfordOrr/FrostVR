/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/GetQueryResultsResult.h"
#include "aws/core/utils/Array.h"
#include "aws/core/utils/json/JsonSerializer.h"

#endif

#include "Model/ResultField.h"
#include "Model/QueryStatistics.h"
#include "Model/QueryStatus.h"

#include "GetQueryResultsResult.generated.h"

USTRUCT(BlueprintType)
struct FGetQueryResultsResult {
GENERATED_BODY()

    /**
    *  <p>The log events that matched the query criteria during the most recent time it ran.</p> <p>The <code>results</code> value is an array of arrays. Each log event is one object in the top-level array. Each of these log event objects is an array of <code>field</code>/<code>value</code> pairs.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString results;

    /**
    *  <p>Includes the number of log events scanned by the query, the number of log events that matched the query criteria, and the total number of bytes in the log events that were scanned. These values reflect the full raw results of the query.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FQueryStatistics statistics;

    /**
    *  <p>The status of the most recent running of the query. Possible values are <code>Cancelled</code>, <code>Complete</code>, <code>Failed</code>, <code>Running</code>, <code>Scheduled</code>, <code>Timeout</code>, and <code>Unknown</code>.</p> <p>Queries time out after 15 minutes of execution. To avoid having your queries time out, reduce the time range being searched or partition your query into a number of queries.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    EAWSQueryStatus status = EAWSQueryStatus::NOT_SET;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FGetQueryResultsResult &fromAWS(const Aws::CloudWatchLogs::Model::GetQueryResultsResult &awsGetQueryResultsResult) {
        const Aws::Vector<Aws::Vector<Aws::CloudWatchLogs::Model::ResultField>>& awsResults = awsGetQueryResultsResult.GetResults();
        Aws::Utils::Array<Aws::Utils::Json::JsonValue> array(awsResults.size());
        for (int i = 0; i < awsResults.size(); i++) {
            Aws::Utils::Array<Aws::Utils::Json::JsonValue> array1(awsResults[i].size());
            for (int j = 0; j < awsResults[i].size(); j++) {
                array1[j] = awsResults[i][j].Jsonize();
            }
            array[i].AsArray(array1);
        }
        this->results = UTF8_TO_TCHAR(Aws::Utils::Json::JsonValue().AsArray(array).View().WriteReadable().c_str());

        this->statistics.fromAWS(awsGetQueryResultsResult.GetStatistics());

        switch(awsGetQueryResultsResult.GetStatus()) {
            case Aws::CloudWatchLogs::Model::QueryStatus::NOT_SET:
                this->status = EAWSQueryStatus::NOT_SET;
                break;
            case Aws::CloudWatchLogs::Model::QueryStatus::Scheduled:
                this->status = EAWSQueryStatus::Scheduled;
                break;
            case Aws::CloudWatchLogs::Model::QueryStatus::Running:
                this->status = EAWSQueryStatus::Running;
                break;
            case Aws::CloudWatchLogs::Model::QueryStatus::Complete:
                this->status = EAWSQueryStatus::Complete;
                break;
            case Aws::CloudWatchLogs::Model::QueryStatus::Failed:
                this->status = EAWSQueryStatus::Failed;
                break;
            case Aws::CloudWatchLogs::Model::QueryStatus::Cancelled:
                this->status = EAWSQueryStatus::Cancelled;
                break;
            case Aws::CloudWatchLogs::Model::QueryStatus::Timeout:
                this->status = EAWSQueryStatus::Timeout;
                break;
            case Aws::CloudWatchLogs::Model::QueryStatus::Unknown:
                this->status = EAWSQueryStatus::Unknown;
                break;
            default:
                this->status = EAWSQueryStatus::NOT_SET;
                break;
        }

        return *this;
    }
#endif
};

/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/QueryInfo.h"

#endif

#include "Model/QueryStatus.h"

#include "QueryInfo.generated.h"

USTRUCT(BlueprintType)
struct FQueryInfo {
GENERATED_BODY()

    /**
    *  <p>The unique ID number of this query.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString queryId;

    /**
    *  <p>The query string used in this query.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString queryString;

    /**
    *  <p>The status of this query. Possible values are <code>Cancelled</code>, <code>Complete</code>, <code>Failed</code>, <code>Running</code>, <code>Scheduled</code>, and <code>Unknown</code>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    EAWSQueryStatus status = EAWSQueryStatus::NOT_SET;

    /**
    *  <p>The date and time that this query was created.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 createTime = 0;

    /**
    *  <p>The name of the log group scanned by this query.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FQueryInfo &fromAWS(const Aws::CloudWatchLogs::Model::QueryInfo &awsQueryInfo) {
        this->queryId = UTF8_TO_TCHAR(awsQueryInfo.GetQueryId().c_str());

        this->queryString = UTF8_TO_TCHAR(awsQueryInfo.GetQueryString().c_str());

        switch(awsQueryInfo.GetStatus()) {
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

        this->createTime = (int64)awsQueryInfo.GetCreateTime();

        this->logGroupName = UTF8_TO_TCHAR(awsQueryInfo.GetLogGroupName().c_str());

        return *this;
    }
#endif
};

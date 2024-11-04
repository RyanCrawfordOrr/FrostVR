/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DescribeQueriesRequest.h"

#endif

#include "Model/QueryStatus.h"

#include "DescribeQueriesRequest.generated.h"

USTRUCT(BlueprintType)
struct FDescribeQueriesRequest {
GENERATED_BODY()

    /**
    *  <p>Limits the returned queries to only those for the specified log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    *  <p>Limits the returned queries to only those that have the specified status. Valid values are <code>Cancelled</code>, <code>Complete</code>, <code>Failed</code>, <code>Running</code>, and <code>Scheduled</code>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    EAWSQueryStatus status = EAWSQueryStatus::NOT_SET;

    /**
    *  <p>Limits the number of returned queries to the specified number.</p>
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
    Aws::CloudWatchLogs::Model::DescribeQueriesRequest toAWS() const {
        Aws::CloudWatchLogs::Model::DescribeQueriesRequest awsDescribeQueriesRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsDescribeQueriesRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

        switch(this->status) {
            case EAWSQueryStatus::Scheduled:
                awsDescribeQueriesRequest.SetStatus(Aws::CloudWatchLogs::Model::QueryStatus::Scheduled);
                break;
            case EAWSQueryStatus::Running:
                awsDescribeQueriesRequest.SetStatus(Aws::CloudWatchLogs::Model::QueryStatus::Running);
                break;
            case EAWSQueryStatus::Complete:
                awsDescribeQueriesRequest.SetStatus(Aws::CloudWatchLogs::Model::QueryStatus::Complete);
                break;
            case EAWSQueryStatus::Failed:
                awsDescribeQueriesRequest.SetStatus(Aws::CloudWatchLogs::Model::QueryStatus::Failed);
                break;
            case EAWSQueryStatus::Cancelled:
                awsDescribeQueriesRequest.SetStatus(Aws::CloudWatchLogs::Model::QueryStatus::Cancelled);
                break;
            case EAWSQueryStatus::Timeout:
                awsDescribeQueriesRequest.SetStatus(Aws::CloudWatchLogs::Model::QueryStatus::Timeout);
                break;
            case EAWSQueryStatus::Unknown:
                awsDescribeQueriesRequest.SetStatus(Aws::CloudWatchLogs::Model::QueryStatus::Unknown);
                break;
            default:
                break;
		}

        if (!(this->maxResults == 0)) {
            awsDescribeQueriesRequest.SetMaxResults(this->maxResults);
        }

		if (!(this->nextToken.IsEmpty())) {
            awsDescribeQueriesRequest.SetNextToken(TCHAR_TO_UTF8(*this->nextToken));
        }

        return awsDescribeQueriesRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty() && status == EAWSQueryStatus::NOT_SET && this->maxResults == 0 && this->nextToken.IsEmpty();
    }
#endif
};

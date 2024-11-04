/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DescribeLogStreamsRequest.h"

#endif

#include "Model/OrderBy.h"

#include "DescribeLogStreamsRequest.generated.h"

USTRUCT(BlueprintType)
struct FDescribeLogStreamsRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    *  <p>Specify either the name or ARN of the log group to view. If the log group is in a source account and you are using a monitoring account, you must use the log group ARN.</p> <p>If you specify values for both <code>logGroupName</code> and <code>logGroupIdentifier</code>, the action returns an <code>InvalidParameterException</code> error.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logs Client")
    FString logGroupIdentifier;

    /**
    *  <p>The prefix to match.</p> <p>If <code>orderBy</code> is <code>LastEventTime</code>, you cannot specify this parameter.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logStreamNamePrefix;

    /**
    *  <p>If the value is <code>LogStreamName</code>, the results are ordered by log stream name. If the value is <code>LastEventTime</code>, the results are ordered by the event time. The default value is <code>LogStreamName</code>.</p> <p>If you order the results by event time, you cannot specify the <code>logStreamNamePrefix</code> parameter.</p> <p> <code>lastEventTimeStamp</code> represents the time of the most recent log event in the log stream in CloudWatch Logs. This number is expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC. <code>lastEventTimeStamp</code> updates on an eventual consistency basis. It typically updates in less than an hour from ingestion, but in rare situations might take longer.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    EAWSOrderBy orderBy = EAWSOrderBy::NOT_SET;

    /**
    *  <p>If the value is true, results are returned in descending order. If the value is to false, results are returned in ascending order. The default value is false.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    bool descending = false;

    /**
    *  <p>The token for the next set of items to return. (You received this token from a previous call.)</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextToken;

    /**
    *  <p>The maximum number of items returned. If you don't specify a value, the default is up to 50 items.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int limit = 0;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::DescribeLogStreamsRequest toAWS() const {
        Aws::CloudWatchLogs::Model::DescribeLogStreamsRequest awsDescribeLogStreamsRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsDescribeLogStreamsRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

		if (!(this->logGroupIdentifier.IsEmpty())) {
            awsDescribeLogStreamsRequest.SetLogGroupIdentifier(TCHAR_TO_UTF8(*this->logGroupIdentifier));
        }

		if (!(this->logStreamNamePrefix.IsEmpty())) {
            awsDescribeLogStreamsRequest.SetLogStreamNamePrefix(TCHAR_TO_UTF8(*this->logStreamNamePrefix));
        }

        switch(this->orderBy) {
            case EAWSOrderBy::LogStreamName:
                awsDescribeLogStreamsRequest.SetOrderBy(Aws::CloudWatchLogs::Model::OrderBy::LogStreamName);
                break;
            case EAWSOrderBy::LastEventTime:
                awsDescribeLogStreamsRequest.SetOrderBy(Aws::CloudWatchLogs::Model::OrderBy::LastEventTime);
                break;
            default:
                break;
		}

        if (!(false)) {
            awsDescribeLogStreamsRequest.SetDescending(this->descending);
        }

		if (!(this->nextToken.IsEmpty())) {
            awsDescribeLogStreamsRequest.SetNextToken(TCHAR_TO_UTF8(*this->nextToken));
        }

        if (!(this->limit == 0)) {
            awsDescribeLogStreamsRequest.SetLimit(this->limit);
        }

        return awsDescribeLogStreamsRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty() && this->logGroupIdentifier.IsEmpty() && this->logStreamNamePrefix.IsEmpty() && orderBy == EAWSOrderBy::NOT_SET && false && this->nextToken.IsEmpty() && this->limit == 0;
    }
#endif
};

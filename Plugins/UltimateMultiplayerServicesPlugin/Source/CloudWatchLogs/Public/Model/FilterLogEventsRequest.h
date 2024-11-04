/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/FilterLogEventsRequest.h"

#endif

#include "FilterLogEventsRequest.generated.h"

USTRUCT(BlueprintType)
struct FFilterLogEventsRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the log group to search.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    *  <p>Specify either the name or ARN of the log group to view log events from. If the log group is in a source account and you are using a monitoring account, you must use the log group ARN.</p> <p>If you specify values for both <code>logGroupName</code> and <code>logGroupIdentifier</code>, the action returns an <code>InvalidParameterException</code> error.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupIdentifier;

    /**
    *  <p>Filters the results to only logs from the log streams in this list.</p> <p>If you specify a value for both <code>logStreamNamePrefix</code> and <code>logStreamNames</code>, the action returns an <code>InvalidParameterException</code> error.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FString> logStreamNames;

    /**
    *  <p>Filters the results to include only events from log streams that have names starting with this prefix.</p> <p>If you specify a value for both <code>logStreamNamePrefix</code> and <code>logStreamNames</code>, but the value for <code>logStreamNamePrefix</code> does not match any log stream names specified in <code>logStreamNames</code>, the action returns an <code>InvalidParameterException</code> error.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logStreamNamePrefix;

    /**
    *  <p>The start of the time range, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC. Events with a timestamp before this time are not returned.</p> <p>If you omit <code>startTime</code> and <code>endTime</code> the most recent log events are retrieved, to up 1 MB or 10,000 log events.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 startTime = 0;

    /**
    *  <p>The end of the time range, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC. Events with a timestamp later than this time are not returned.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 endTime = 0;

    /**
    *  <p>The filter pattern to use. For more information, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/logs/FilterAndPatternSyntax.html">Filter and Pattern Syntax</a>.</p> <p>If not provided, all the events are matched.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString filterPattern;

    /**
    *  <p>The token for the next set of events to return. (You received this token from a previous call.)</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextToken;

    /**
    *  <p>The maximum number of events to return. The default is 10,000 events.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int limit = 0;

    /**
    *  <p>Specify <code>true</code> to display the log event fields with all sensitive data unmasked and visible. The default is <code>false</code>.</p> <p>To use this operation with this parameter, you must be signed into an account with the <code>logs:Unmask</code> permission.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    bool unmask = false;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::FilterLogEventsRequest toAWS() const {
        Aws::CloudWatchLogs::Model::FilterLogEventsRequest awsFilterLogEventsRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsFilterLogEventsRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

		if (!(this->logGroupIdentifier.IsEmpty())) {
            awsFilterLogEventsRequest.SetLogGroupIdentifier(TCHAR_TO_UTF8(*this->logGroupIdentifier));
        }

        for (const FString& elem : this->logStreamNames) {
            awsFilterLogEventsRequest.AddLogStreamNames(TCHAR_TO_UTF8(*elem));
        }

		if (!(this->logStreamNamePrefix.IsEmpty())) {
            awsFilterLogEventsRequest.SetLogStreamNamePrefix(TCHAR_TO_UTF8(*this->logStreamNamePrefix));
        }

        if (!(this->startTime == 0)) {
            awsFilterLogEventsRequest.SetStartTime(this->startTime);
        }

        if (!(this->endTime == 0)) {
            awsFilterLogEventsRequest.SetEndTime(this->endTime);
        }

		if (!(this->filterPattern.IsEmpty())) {
            awsFilterLogEventsRequest.SetFilterPattern(TCHAR_TO_UTF8(*this->filterPattern));
        }

		if (!(this->nextToken.IsEmpty())) {
            awsFilterLogEventsRequest.SetNextToken(TCHAR_TO_UTF8(*this->nextToken));
        }

        if (!(this->limit == 0)) {
            awsFilterLogEventsRequest.SetLimit(this->limit);
        }

        awsFilterLogEventsRequest.SetUnmask(this->unmask);

        return awsFilterLogEventsRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty() && this->logGroupIdentifier.IsEmpty() && this->logStreamNames.Num() == 0 && this->logStreamNamePrefix.IsEmpty() && this->startTime == 0 && this->endTime == 0 && this->filterPattern.IsEmpty() && this->nextToken.IsEmpty() && this->limit == 0 && false;
    }
#endif
};

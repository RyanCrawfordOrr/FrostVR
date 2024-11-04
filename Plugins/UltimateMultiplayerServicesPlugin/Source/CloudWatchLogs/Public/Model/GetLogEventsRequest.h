/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/GetLogEventsRequest.h"

#endif

#include "GetLogEventsRequest.generated.h"

USTRUCT(BlueprintType)
struct FGetLogEventsRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    *  <p>Specify either the name or ARN of the log group to view events from. If the log group is in a source account and you are using a monitoring account, you must use the log group ARN.</p> <p> If you specify values for both <code>logGroupName</code> and <code>logGroupIdentifier</code>, the action returns an <code>InvalidParameterException</code> error.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupIdentifier;

    /**
    *  <p>The name of the log stream.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logStreamName;

    /**
    *  <p>The start of the time range, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC. Events with a timestamp equal to this time or later than this time are included. Events with a timestamp earlier than this time are not included.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 startTime = 0;

    /**
    *  <p>The end of the time range, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC. Events with a timestamp equal to or later than this time are not included.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 endTime = 0;

    /**
    *  <p>The token for the next set of items to return. (You received this token from a previous call.)</p> <p>Using this token works only when you specify <code>true</code> for <code>startFromHead</code>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextToken;

    /**
    *  <p>The maximum number of log events returned. If you don't specify a value, the maximum is as many log events as can fit in a response size of 1 MB, up to 10,000 log events.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int limit = 0;

    /**
    *  <p>If the value is true, the earliest log events are returned first. If the value is false, the latest log events are returned first. The default value is false.</p> <p>If you are using <code>nextToken</code> in this operation, you must specify <code>true</code> for <code>startFromHead</code>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    bool startFromHead = false;

    /**
    *  <p>Specify <code>true</code> to display the log event fields with all sensitive data unmasked and visible. The default is <code>false</code>.</p> <p>To use this operation with this parameter, you must be signed into an account with the <code>logs:Unmask</code> permission.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    bool unmask = false;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::GetLogEventsRequest toAWS() const {
        Aws::CloudWatchLogs::Model::GetLogEventsRequest awsGetLogEventsRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsGetLogEventsRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

		if (!(this->logGroupIdentifier.IsEmpty())) {
            awsGetLogEventsRequest.SetLogGroupIdentifier(TCHAR_TO_UTF8(*this->logGroupIdentifier));
        }

		if (!(this->logStreamName.IsEmpty())) {
            awsGetLogEventsRequest.SetLogStreamName(TCHAR_TO_UTF8(*this->logStreamName));
        }

        if (!(this->startTime == 0)) {
            awsGetLogEventsRequest.SetStartTime(this->startTime);
        }

        if (!(this->endTime == 0)) {
            awsGetLogEventsRequest.SetEndTime(this->endTime);
        }

		if (!(this->nextToken.IsEmpty())) {
            awsGetLogEventsRequest.SetNextToken(TCHAR_TO_UTF8(*this->nextToken));
        }

        if (!(this->limit == 0)) {
            awsGetLogEventsRequest.SetLimit(this->limit);
        }

        if (!(false)) {
            awsGetLogEventsRequest.SetStartFromHead(this->startFromHead);
        }

        awsGetLogEventsRequest.SetUnmask(this->unmask);

        return awsGetLogEventsRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty() && this->logGroupIdentifier.IsEmpty() && this->logStreamName.IsEmpty() && this->startTime == 0 && this->endTime == 0 && this->nextToken.IsEmpty() && this->limit == 0 && false && false;
    }
#endif
};

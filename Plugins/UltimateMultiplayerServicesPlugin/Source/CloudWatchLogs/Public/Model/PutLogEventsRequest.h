/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/PutLogEventsRequest.h"

#endif

#include "Model/InputLogEvent.h"

#include "PutLogEventsRequest.generated.h"

USTRUCT(BlueprintType)
struct FPutLogEventsRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    *  <p>The name of the log stream.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logStreamName;

    /**
    *  <p>The log events.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FInputLogEvent> logEvents;

    /**
    *  <p>The sequence token obtained from the response of the previous <code>PutLogEvents</code> call. An upload in a newly created log stream does not require a sequence token. You can also get the sequence token using <a href="https://docs.aws.amazon.com/AmazonCloudWatchLogs/latest/APIReference/API_DescribeLogStreams.html">DescribeLogStreams</a>. If you call <code>PutLogEvents</code> twice within a narrow time period using the same value for <code>sequenceToken</code>, both calls might be successful or one might be rejected.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString sequenceToken;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::PutLogEventsRequest toAWS() const {
        Aws::CloudWatchLogs::Model::PutLogEventsRequest awsPutLogEventsRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsPutLogEventsRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

		if (!(this->logStreamName.IsEmpty())) {
            awsPutLogEventsRequest.SetLogStreamName(TCHAR_TO_UTF8(*this->logStreamName));
        }

        for (const FInputLogEvent& elem : this->logEvents) {
            awsPutLogEventsRequest.AddLogEvents(elem.toAWS());
        }

		if (!(this->sequenceToken.IsEmpty())) {
            awsPutLogEventsRequest.SetSequenceToken(TCHAR_TO_UTF8(*this->sequenceToken));
        }

        return awsPutLogEventsRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty() && this->logStreamName.IsEmpty() && this->logEvents.Num() == 0 && this->sequenceToken.IsEmpty();
    }
#endif
};

/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/GetLogGroupFieldsRequest.h"

#endif

#include "GetLogGroupFieldsRequest.generated.h"

USTRUCT(BlueprintType)
struct FGetLogGroupFieldsRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the log group to search.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    *  <p>The time to set as the center of the query. If you specify <code>time</code>, the 8 minutes before and 8 minutes after this time are searched. If you omit <code>time</code>, the past 15 minutes are queried.</p> <p>The <code>time</code> value is specified as epoch time, the number of seconds since January 1, 1970, 00:00:00 UTC.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 time = 0;

    /**
    *  <p>Specify either the name or ARN of the log group to view. If the log group is in a source account and you are using a monitoring account, you must specify the ARN.</p> <p>If you specify values for both <code>logGroupName</code> and <code>logGroupIdentifier</code>, the action returns an <code>InvalidParameterException</code> error.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupIdentifier;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::GetLogGroupFieldsRequest toAWS() const {
        Aws::CloudWatchLogs::Model::GetLogGroupFieldsRequest awsGetLogGroupFieldsRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsGetLogGroupFieldsRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

        if (!(this->time == 0)) {
            awsGetLogGroupFieldsRequest.SetTime(this->time);
        }

		if (!(this->logGroupIdentifier.IsEmpty())) {
            awsGetLogGroupFieldsRequest.SetLogGroupIdentifier(TCHAR_TO_UTF8(*this->logGroupIdentifier));
        }

        return awsGetLogGroupFieldsRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty() && this->time == 0 && this->logGroupIdentifier.IsEmpty();
    }
#endif
};

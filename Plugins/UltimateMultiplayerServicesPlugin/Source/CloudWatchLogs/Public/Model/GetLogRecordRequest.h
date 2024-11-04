/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/GetLogRecordRequest.h"

#endif

#include "GetLogRecordRequest.generated.h"

USTRUCT(BlueprintType)
struct FGetLogRecordRequest {
GENERATED_BODY()

    /**
    *  <p>The pointer corresponding to the log event record you want to retrieve. You get this from the response of a <code>GetQueryResults</code> operation. In that response, the value of the <code>@ptr</code> field for a log event is the value to use as <code>logRecordPointer</code> to retrieve that complete log event record.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logRecordPointer;

    /**
    *  <p>Specify <code>true</code> to display the log event fields with all sensitive data unmasked and visible. The default is <code>false</code>.</p> <p>To use this operation with this parameter, you must be signed into an account with the <code>logs:Unmask</code> permission.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    bool unmask = false;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::GetLogRecordRequest toAWS() const {
        Aws::CloudWatchLogs::Model::GetLogRecordRequest awsGetLogRecordRequest;

		if (!(this->logRecordPointer.IsEmpty())) {
            awsGetLogRecordRequest.SetLogRecordPointer(TCHAR_TO_UTF8(*this->logRecordPointer));
        }

        awsGetLogRecordRequest.SetUnmask(this->unmask);

        return awsGetLogRecordRequest;
    }

    bool IsEmpty() const {
        return this->logRecordPointer.IsEmpty() && false;
    }
#endif
};

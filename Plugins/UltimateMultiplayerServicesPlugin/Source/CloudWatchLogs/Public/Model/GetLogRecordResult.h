/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/GetLogRecordResult.h"

#endif

#include "GetLogRecordResult.generated.h"

USTRUCT(BlueprintType)
struct FGetLogRecordResult {
GENERATED_BODY()

    /**
    *  <p>The requested log event, as a JSON string.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TMap<FString, FString> logRecord;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FGetLogRecordResult &fromAWS(const Aws::CloudWatchLogs::Model::GetLogRecordResult &awsGetLogRecordResult) {
        this->logRecord.Empty();
        for (const auto& elem : awsGetLogRecordResult.GetLogRecord()) {
            this->logRecord.Add(UTF8_TO_TCHAR(elem.first.c_str()), UTF8_TO_TCHAR(elem.second.c_str()));
        }

        return *this;
    }
#endif
};

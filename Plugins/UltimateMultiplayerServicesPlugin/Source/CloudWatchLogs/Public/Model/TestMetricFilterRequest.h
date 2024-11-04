/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/TestMetricFilterRequest.h"

#endif

#include "TestMetricFilterRequest.generated.h"

USTRUCT(BlueprintType)
struct FTestMetricFilterRequest {
GENERATED_BODY()

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString filterPattern;

    /**
    *  <p>The log event messages to test.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FString> logEventMessages;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::TestMetricFilterRequest toAWS() const {
        Aws::CloudWatchLogs::Model::TestMetricFilterRequest awsTestMetricFilterRequest;

		if (!(this->filterPattern.IsEmpty())) {
            awsTestMetricFilterRequest.SetFilterPattern(TCHAR_TO_UTF8(*this->filterPattern));
        }

        for (const FString& elem : this->logEventMessages) {
            awsTestMetricFilterRequest.AddLogEventMessages(TCHAR_TO_UTF8(*elem));
        }

        return awsTestMetricFilterRequest;
    }

    bool IsEmpty() const {
        return this->filterPattern.IsEmpty() && this->logEventMessages.Num() == 0;
    }
#endif
};

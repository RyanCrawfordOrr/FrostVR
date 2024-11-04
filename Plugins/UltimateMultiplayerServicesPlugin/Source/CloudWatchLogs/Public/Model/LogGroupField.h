/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/LogGroupField.h"

#endif

#include "LogGroupField.generated.h"

USTRUCT(BlueprintType)
struct FLogGroupField {
GENERATED_BODY()

    /**
    *  <p>The name of a log field.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString name;

    /**
    *  <p>The percentage of log events queried that contained the field.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int percent = 0;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FLogGroupField &fromAWS(const Aws::CloudWatchLogs::Model::LogGroupField &awsLogGroupField) {
        this->name = UTF8_TO_TCHAR(awsLogGroupField.GetName().c_str());

		this->percent = awsLogGroupField.GetPercent();

        return *this;
    }
#endif
};

/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/ResultField.h"

#endif

#include "ResultField.generated.h"

USTRUCT(BlueprintType)
struct FResultField {
GENERATED_BODY()

    /**
    *  <p>The log event field.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString field;

    /**
    *  <p>The value of this field.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString value;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FResultField &fromAWS(const Aws::CloudWatchLogs::Model::ResultField &awsResultField) {
        this->field = UTF8_TO_TCHAR(awsResultField.GetField().c_str());

        this->value = UTF8_TO_TCHAR(awsResultField.GetValue().c_str());

        return *this;
    }
#endif
};

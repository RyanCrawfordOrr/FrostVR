/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/GetLogGroupFieldsResult.h"

#endif

#include "Model/LogGroupField.h"

#include "GetLogGroupFieldsResult.generated.h"

USTRUCT(BlueprintType)
struct FGetLogGroupFieldsResult {
GENERATED_BODY()

    /**
    *  <p>The array of fields found in the query. Each object in the array contains the name of the field, along with the percentage of time it appeared in the log events that were queried.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FLogGroupField> logGroupFields;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FGetLogGroupFieldsResult &fromAWS(const Aws::CloudWatchLogs::Model::GetLogGroupFieldsResult &awsGetLogGroupFieldsResult) {
        this->logGroupFields.Empty();
        for (const Aws::CloudWatchLogs::Model::LogGroupField& elem : awsGetLogGroupFieldsResult.GetLogGroupFields()) {
            this->logGroupFields.Add(FLogGroupField().fromAWS(elem));
        }

        return *this;
    }
#endif
};

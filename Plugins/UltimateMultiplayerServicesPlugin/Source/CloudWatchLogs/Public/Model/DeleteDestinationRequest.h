/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DeleteDestinationRequest.h"

#endif

#include "DeleteDestinationRequest.generated.h"

USTRUCT(BlueprintType)
struct FDeleteDestinationRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the destination.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString destinationName;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::DeleteDestinationRequest toAWS() const {
        Aws::CloudWatchLogs::Model::DeleteDestinationRequest awsDeleteDestinationRequest;

		if (!(this->destinationName.IsEmpty())) {
            awsDeleteDestinationRequest.SetDestinationName(TCHAR_TO_UTF8(*this->destinationName));
        }

        return awsDeleteDestinationRequest;
    }

    bool IsEmpty() const {
        return this->destinationName.IsEmpty();
    }
#endif
};

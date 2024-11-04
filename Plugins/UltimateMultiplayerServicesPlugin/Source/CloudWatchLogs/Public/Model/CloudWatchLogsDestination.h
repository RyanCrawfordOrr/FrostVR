/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/Destination.h"

#endif


#include "CloudWatchLogsDestination.generated.h"

USTRUCT(BlueprintType)
struct FCloudWatchLogsDestination {
GENERATED_BODY()

    /**
    *  <p>The name of the destination.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString destinationName;

    /**
    *  <p>The Amazon Resource Name (ARN) of the physical target where the log events are delivered (for example, a Kinesis stream).</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString targetArn;

    /**
    *  <p>A role for impersonation, used when delivering log events to the target.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString roleArn;

    /**
    *  <p>An IAM policy document that governs which AWS accounts can create subscription filters against this destination.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString accessPolicy;

    /**
    *  <p>The ARN of this destination.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString arn;

    /**
    *  <p>The creation time of the destination, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 creationTime = 0;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FCloudWatchLogsDestination &fromAWS(const Aws::CloudWatchLogs::Model::Destination &awsDestination) {
        this->destinationName = UTF8_TO_TCHAR(awsDestination.GetDestinationName().c_str());

        this->targetArn = UTF8_TO_TCHAR(awsDestination.GetTargetArn().c_str());

        this->roleArn = UTF8_TO_TCHAR(awsDestination.GetRoleArn().c_str());

        this->accessPolicy = UTF8_TO_TCHAR(awsDestination.GetAccessPolicy().c_str());

        this->arn = UTF8_TO_TCHAR(awsDestination.GetArn().c_str());

        this->creationTime = (int64)awsDestination.GetCreationTime();

        return *this;
    }
#endif
};

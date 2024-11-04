/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/LogGroup.h"

#endif

#include "Model/AWSCloudWatchLogsDataProtectionStatus.h"

#include "LogGroup.generated.h"

USTRUCT(BlueprintType)
struct FLogGroup {
GENERATED_BODY()

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    *  <p>The creation time of the log group, expressed as the number of milliseconds after Jan 1, 1970 00:00:00 UTC.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 creationTime = 0;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int retentionInDays = 0;

    /**
    *  <p>The number of metric filters.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int metricFilterCount = 0;

    /**
    *  <p>The Amazon Resource Name (ARN) of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString arn;

    /**
    *  <p>The number of bytes stored.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 storedBytes = 0;

    /**
    *  <p>The Amazon Resource Name (ARN) of the CMK to use when encrypting log data.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString kmsKeyId;

    /**
    *  <p>Displays whether this log group has a protection policy, or whether it had one in the past. For more information, see <a href="https://docs.aws.amazon.com/AmazonCloudWatchLogs/latest/APIReference/API_PutDataProtectionPolicy.html">PutDataProtectionPolicy</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    EAWSCloudWatchLogsDataProtectionStatus dataProtectionStatus = EAWSCloudWatchLogsDataProtectionStatus::NOT_SET;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FLogGroup &fromAWS(const Aws::CloudWatchLogs::Model::LogGroup &awsLogGroup) {
        this->logGroupName = UTF8_TO_TCHAR(awsLogGroup.GetLogGroupName().c_str());

        this->creationTime = (int64)awsLogGroup.GetCreationTime();

		this->retentionInDays = awsLogGroup.GetRetentionInDays();

		this->metricFilterCount = awsLogGroup.GetMetricFilterCount();

        this->arn = UTF8_TO_TCHAR(awsLogGroup.GetArn().c_str());

        this->storedBytes = (int64)awsLogGroup.GetStoredBytes();

        this->kmsKeyId = UTF8_TO_TCHAR(awsLogGroup.GetKmsKeyId().c_str());

        switch(awsLogGroup.GetDataProtectionStatus()) {
            case Aws::CloudWatchLogs::Model::DataProtectionStatus::NOT_SET:
                this->dataProtectionStatus = EAWSCloudWatchLogsDataProtectionStatus::NOT_SET;
                break;
            case Aws::CloudWatchLogs::Model::DataProtectionStatus::ACTIVATED:
                this->dataProtectionStatus = EAWSCloudWatchLogsDataProtectionStatus::ACTIVATED;
                break;
            case Aws::CloudWatchLogs::Model::DataProtectionStatus::DELETED:
                this->dataProtectionStatus = EAWSCloudWatchLogsDataProtectionStatus::DELETED;
                break;
            case Aws::CloudWatchLogs::Model::DataProtectionStatus::ARCHIVED:
                this->dataProtectionStatus = EAWSCloudWatchLogsDataProtectionStatus::ARCHIVED;
                break;
            case Aws::CloudWatchLogs::Model::DataProtectionStatus::DISABLED:
                this->dataProtectionStatus = EAWSCloudWatchLogsDataProtectionStatus::DISABLED;
                break;
            default:
                this->dataProtectionStatus = EAWSCloudWatchLogsDataProtectionStatus::NOT_SET;
                break;
        }

        return *this;
    }
#endif
};

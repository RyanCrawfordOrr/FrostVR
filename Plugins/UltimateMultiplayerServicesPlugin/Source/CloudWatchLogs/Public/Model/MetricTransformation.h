/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/MetricTransformation.h"

#endif

#include "Model/AWSCloudWatchLogsStandardUnit.h"

#include "MetricTransformation.generated.h"

USTRUCT(BlueprintType)
struct FMetricTransformation {
GENERATED_BODY()

    /**
    *  <p>The name of the CloudWatch metric.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString metricName;

    /**
    *  <p>A custom namespace to contain your metric in CloudWatch. Use namespaces to group together metrics that are similar. For more information, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/monitoring/cloudwatch_concepts.html#Namespace">Namespaces</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString metricNamespace;

    /**
    *  <p>The value to publish to the CloudWatch metric when a filter pattern matches a log event.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString metricValue;

    /**
    *  <p>(Optional) The value to emit when a filter pattern does not match a log event. This value can be null.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    float defaultValue = 0.0f;
    /**
    *  <p>The fields to use as dimensions for the metric. One metric filter can include as many as three dimensions.</p>  <p>Metrics extracted from log events are charged as custom metrics. To prevent unexpected high charges, do not specify high-cardinality fields such as <code>IPAddress</code> or <code>requestID</code> as dimensions. Each different value found for a dimension is treated as a separate metric and accrues charges as a separate custom metric. </p> <p>CloudWatch Logs disables a metric filter if it generates 1000 different name/value pairs for your specified dimensions within a certain amount of time. This helps to prevent accidental high charges.</p> <p>You can also set up a billing alarm to alert you if your charges are higher than expected. For more information, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/monitoring/monitor_estimated_charges_with_cloudwatch.html"> Creating a Billing Alarm to Monitor Your Estimated Amazon Web Services Charges</a>. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TMap<FString, FString> dimensions;

    /**
    *  <p>The unit to assign to the metric. If you omit this, the unit is set as <code>None</code>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    EAWSCloudWatchLogsStandardUnit unit = EAWSCloudWatchLogsStandardUnit::NOT_SET;;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::MetricTransformation toAWS() const {
        Aws::CloudWatchLogs::Model::MetricTransformation awsMetricTransformation;

		if (!(this->metricName.IsEmpty())) {
            awsMetricTransformation.SetMetricName(TCHAR_TO_UTF8(*this->metricName));
        }

		if (!(this->metricNamespace.IsEmpty())) {
            awsMetricTransformation.SetMetricNamespace(TCHAR_TO_UTF8(*this->metricNamespace));
        }

		if (!(this->metricValue.IsEmpty())) {
            awsMetricTransformation.SetMetricValue(TCHAR_TO_UTF8(*this->metricValue));
        }

        if (!(this->defaultValue <= 0)) {
            awsMetricTransformation.SetDefaultValue(this->defaultValue);
        }

        for (const TPair<FString, FString>& elem : this->dimensions) {
            awsMetricTransformation.AddDimensions(TCHAR_TO_UTF8(*elem.Key), TCHAR_TO_UTF8(*elem.Value));
        }

        switch(this->unit) {
            case EAWSCloudWatchLogsStandardUnit::Seconds:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Seconds);
                break;
            case EAWSCloudWatchLogsStandardUnit::Microseconds:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Microseconds);
                break;
            case EAWSCloudWatchLogsStandardUnit::Milliseconds:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Milliseconds);
                break;
            case EAWSCloudWatchLogsStandardUnit::Bytes:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Bytes);
                break;
            case EAWSCloudWatchLogsStandardUnit::Kilobytes:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Kilobytes);
                break;
            case EAWSCloudWatchLogsStandardUnit::Megabytes:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Megabytes);
                break;
            case EAWSCloudWatchLogsStandardUnit::Gigabytes:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Gigabytes);
                break;
            case EAWSCloudWatchLogsStandardUnit::Terabytes:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Terabytes);
                break;
            case EAWSCloudWatchLogsStandardUnit::Bits:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Bits);
                break;
            case EAWSCloudWatchLogsStandardUnit::Kilobits:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Kilobits);
                break;
            case EAWSCloudWatchLogsStandardUnit::Megabits:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Megabits);
                break;
            case EAWSCloudWatchLogsStandardUnit::Gigabits:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Gigabits);
                break;
            case EAWSCloudWatchLogsStandardUnit::Terabits:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Terabits);
                break;
            case EAWSCloudWatchLogsStandardUnit::Percent:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Percent);
                break;
            case EAWSCloudWatchLogsStandardUnit::Count:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Count);
                break;
            case EAWSCloudWatchLogsStandardUnit::Bytes_Second:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Bytes_Second);
                break;
            case EAWSCloudWatchLogsStandardUnit::Kilobytes_Second:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Kilobytes_Second);
                break;
            case EAWSCloudWatchLogsStandardUnit::Megabytes_Second:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Megabytes_Second);
                break;
            case EAWSCloudWatchLogsStandardUnit::Gigabytes_Second:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Gigabytes_Second);
                break;
            case EAWSCloudWatchLogsStandardUnit::Terabytes_Second:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Terabytes_Second);
                break;
            case EAWSCloudWatchLogsStandardUnit::Bits_Second:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Bits_Second);
                break;
            case EAWSCloudWatchLogsStandardUnit::Kilobits_Second:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Kilobits_Second);
                break;
            case EAWSCloudWatchLogsStandardUnit::Megabits_Second:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Megabits_Second);
                break;
            case EAWSCloudWatchLogsStandardUnit::Gigabits_Second:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Gigabits_Second);
                break;
            case EAWSCloudWatchLogsStandardUnit::Terabits_Second:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Terabits_Second);
                break;
            case EAWSCloudWatchLogsStandardUnit::Count_Second:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::Count_Second);
                break;
            case EAWSCloudWatchLogsStandardUnit::None:
                awsMetricTransformation.SetUnit(Aws::CloudWatchLogs::Model::StandardUnit::None);
                break;
            default:
                break;
        }

        return awsMetricTransformation;
    }

    bool IsEmpty() const {
        return this->metricName.IsEmpty() && this->metricNamespace.IsEmpty() && this->metricValue.IsEmpty() && this->defaultValue <= 0 && this->dimensions.Num() == 0 && unit == EAWSCloudWatchLogsStandardUnit::NOT_SET;
    }

    FMetricTransformation &fromAWS(const Aws::CloudWatchLogs::Model::MetricTransformation &awsMetricTransformation) {
        this->metricName = UTF8_TO_TCHAR(awsMetricTransformation.GetMetricName().c_str());

        this->metricNamespace = UTF8_TO_TCHAR(awsMetricTransformation.GetMetricNamespace().c_str());

        this->metricValue = UTF8_TO_TCHAR(awsMetricTransformation.GetMetricValue().c_str());

        this->defaultValue = (float)awsMetricTransformation.GetDefaultValue();

        this->dimensions.Empty();
        for (const auto& elem : awsMetricTransformation.GetDimensions()) {
            this->dimensions.Add(UTF8_TO_TCHAR(elem.first.c_str()), UTF8_TO_TCHAR(elem.second.c_str()));
        }

        switch(awsMetricTransformation.GetUnit()) {
            case Aws::CloudWatchLogs::Model::StandardUnit::NOT_SET:
                this->unit = EAWSCloudWatchLogsStandardUnit::NOT_SET;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Seconds:
                this->unit = EAWSCloudWatchLogsStandardUnit::Seconds;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Microseconds:
                this->unit = EAWSCloudWatchLogsStandardUnit::Microseconds;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Milliseconds:
                this->unit = EAWSCloudWatchLogsStandardUnit::Milliseconds;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Bytes:
                this->unit = EAWSCloudWatchLogsStandardUnit::Bytes;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Kilobytes:
                this->unit = EAWSCloudWatchLogsStandardUnit::Kilobytes;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Megabytes:
                this->unit = EAWSCloudWatchLogsStandardUnit::Megabytes;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Gigabytes:
                this->unit = EAWSCloudWatchLogsStandardUnit::Gigabytes;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Terabytes:
                this->unit = EAWSCloudWatchLogsStandardUnit::Terabytes;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Bits:
                this->unit = EAWSCloudWatchLogsStandardUnit::Bits;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Kilobits:
                this->unit = EAWSCloudWatchLogsStandardUnit::Kilobits;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Megabits:
                this->unit = EAWSCloudWatchLogsStandardUnit::Megabits;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Gigabits:
                this->unit = EAWSCloudWatchLogsStandardUnit::Gigabits;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Terabits:
                this->unit = EAWSCloudWatchLogsStandardUnit::Terabits;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Percent:
                this->unit = EAWSCloudWatchLogsStandardUnit::Percent;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Count:
                this->unit = EAWSCloudWatchLogsStandardUnit::Count;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Bytes_Second:
                this->unit = EAWSCloudWatchLogsStandardUnit::Bytes_Second;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Kilobytes_Second:
                this->unit = EAWSCloudWatchLogsStandardUnit::Kilobytes_Second;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Megabytes_Second:
                this->unit = EAWSCloudWatchLogsStandardUnit::Megabytes_Second;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Gigabytes_Second:
                this->unit = EAWSCloudWatchLogsStandardUnit::Gigabytes_Second;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Terabytes_Second:
                this->unit = EAWSCloudWatchLogsStandardUnit::Terabytes_Second;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Bits_Second:
                this->unit = EAWSCloudWatchLogsStandardUnit::Bits_Second;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Kilobits_Second:
                this->unit = EAWSCloudWatchLogsStandardUnit::Kilobits_Second;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Megabits_Second:
                this->unit = EAWSCloudWatchLogsStandardUnit::Megabits_Second;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Gigabits_Second:
                this->unit = EAWSCloudWatchLogsStandardUnit::Gigabits_Second;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Terabits_Second:
                this->unit = EAWSCloudWatchLogsStandardUnit::Terabits_Second;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::Count_Second:
                this->unit = EAWSCloudWatchLogsStandardUnit::Count_Second;
                break;
            case Aws::CloudWatchLogs::Model::StandardUnit::None:
                this->unit = EAWSCloudWatchLogsStandardUnit::None;
                break;
            default:
                this->unit = EAWSCloudWatchLogsStandardUnit::NOT_SET;
                break;
        }

        return *this;
    }
#endif
};

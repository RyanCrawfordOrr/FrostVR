/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DescribeMetricFiltersRequest.h"

#endif

#include "DescribeMetricFiltersRequest.generated.h"

USTRUCT(BlueprintType)
struct FDescribeMetricFiltersRequest {
GENERATED_BODY()

    /**
    *  <p>The name of the log group.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    *  <p>The prefix to match. CloudWatch Logs uses the value you set here only if you also include the <code>logGroupName</code> parameter in your request.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString filterNamePrefix;

    /**
    *  <p>The token for the next set of items to return. (You received this token from a previous call.)</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextToken;

    /**
    *  <p>The maximum number of items returned. If you don't specify a value, the default is up to 50 items.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int limit = 0;

    /**
    *  <p>Filters results to include only those with the specified metric name. If you include this parameter in your request, you must also include the <code>metricNamespace</code> parameter.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString metricName;

    /**
    *  <p>Filters results to include only those in the specified namespace. If you include this parameter in your request, you must also include the <code>metricName</code> parameter.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString metricNamespace;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::DescribeMetricFiltersRequest toAWS() const {
        Aws::CloudWatchLogs::Model::DescribeMetricFiltersRequest awsDescribeMetricFiltersRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsDescribeMetricFiltersRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

		if (!(this->filterNamePrefix.IsEmpty())) {
            awsDescribeMetricFiltersRequest.SetFilterNamePrefix(TCHAR_TO_UTF8(*this->filterNamePrefix));
        }

		if (!(this->nextToken.IsEmpty())) {
            awsDescribeMetricFiltersRequest.SetNextToken(TCHAR_TO_UTF8(*this->nextToken));
        }

        if (!(this->limit == 0)) {
            awsDescribeMetricFiltersRequest.SetLimit(this->limit);
        }

		if (!(this->metricName.IsEmpty())) {
            awsDescribeMetricFiltersRequest.SetMetricName(TCHAR_TO_UTF8(*this->metricName));
        }

		if (!(this->metricNamespace.IsEmpty())) {
            awsDescribeMetricFiltersRequest.SetMetricNamespace(TCHAR_TO_UTF8(*this->metricNamespace));
        }

        return awsDescribeMetricFiltersRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty() && this->filterNamePrefix.IsEmpty() && this->nextToken.IsEmpty() && this->limit == 0 && this->metricName.IsEmpty() && this->metricNamespace.IsEmpty();
    }
#endif
};

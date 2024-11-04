/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/StartQueryRequest.h"

#endif

#include "StartQueryRequest.generated.h"

USTRUCT(BlueprintType)
struct FStartQueryRequest {
GENERATED_BODY()

    /**
    *  <p>The log group on which to perform the query.</p> <p>A <code>StartQuery</code> operation must include a <code>logGroupNames</code> or a <code>logGroupName</code> parameter, but not both.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupName;

    /**
    *  <p>The list of log groups to be queried. You can include up to 20 log groups.</p> <p>A <code>StartQuery</code> operation must include a <code>logGroupNames</code> or a <code>logGroupName</code> parameter, but not both.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FString> logGroupNames;

    /**
    *  <p>The list of log groups to query. You can include up to 50 log groups.</p> <p>You can specify them by the log group name or ARN. If a log group that you're querying is in a source account and you're using a monitoring account, you must specify the ARN of the log group here. The query definition must also be defined in the monitoring account.</p> <p>If you specify an ARN, the ARN can't end with an asterisk (*).</p> <p>A <code>StartQuery</code> operation must include exactly one of the following parameters: <code>logGroupName</code>, <code>logGroupNames</code> or <code>logGroupIdentifiers</code>. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FString> logGroupIdentifiers;

    /**
    *  <p>The beginning of the time range to query. The range is inclusive, so the specified start time is included in the query. Specified as epoch time, the number of seconds since January 1, 1970, 00:00:00 UTC.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 startTime = 0;

    /**
    *  <p>The end of the time range to query. The range is inclusive, so the specified end time is included in the query. Specified as epoch time, the number of seconds since January 1, 1970, 00:00:00 UTC.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int64 endTime = 0;

    /**
    *  <p>The query string to use. For more information, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/logs/CWL_QuerySyntax.html">CloudWatch Logs Insights Query Syntax</a>.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString queryString;

    /**
    *  <p>The maximum number of log events to return in the query. If the query string uses the <code>fields</code> command, only the specified fields and their values are returned. The default is 1000.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    int limit = 0;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::StartQueryRequest toAWS() const {
        Aws::CloudWatchLogs::Model::StartQueryRequest awsStartQueryRequest;

		if (!(this->logGroupName.IsEmpty())) {
            awsStartQueryRequest.SetLogGroupName(TCHAR_TO_UTF8(*this->logGroupName));
        }

        for (const FString& elem : this->logGroupNames) {
            awsStartQueryRequest.AddLogGroupNames(TCHAR_TO_UTF8(*elem));
        }

        for (const FString& elem : this->logGroupIdentifiers) {
            awsStartQueryRequest.AddLogGroupIdentifiers(TCHAR_TO_UTF8(*elem));
        }

        if (!(this->startTime == 0)) {
            awsStartQueryRequest.SetStartTime(this->startTime);
        }

        if (!(this->endTime == 0)) {
            awsStartQueryRequest.SetEndTime(this->endTime);
        }

		if (!(this->queryString.IsEmpty())) {
            awsStartQueryRequest.SetQueryString(TCHAR_TO_UTF8(*this->queryString));
        }

        if (!(this->limit == 0)) {
            awsStartQueryRequest.SetLimit(this->limit);
        }

        return awsStartQueryRequest;
    }

    bool IsEmpty() const {
        return this->logGroupName.IsEmpty() && this->logGroupNames.Num() == 0 && this->logGroupIdentifiers.Num() == 0 && this->startTime == 0 && this->endTime == 0 && this->queryString.IsEmpty() && this->limit == 0;
    }
#endif
};

/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DescribeLogGroupsRequest.h"

#endif

#include "DescribeLogGroupsRequest.generated.h"

USTRUCT(BlueprintType)
struct FDescribeLogGroupsRequest {
GENERATED_BODY()

    /**
    *  <p>When <code>includeLinkedAccounts</code> is set to <code>True</code>, use this parameter to specify the list of accounts to search. You can specify as many as 20 account IDs in the array. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logs Client")
    TArray<FString> accountIdentifiers;

    /**
    *  <p>The prefix to match.</p>  <p> <code>logGroupNamePrefix</code> and <code>logGroupNamePattern</code> are mutually exclusive. Only one of these parameters can be passed. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupNamePrefix;

    /**
    *  <p>If you specify a string for this parameter, the operation returns only log groups that have names that match the string based on a case-sensitive substring search. For example, if you specify <code>Foo</code>, log groups named <code>FooBar</code>, <code>aws/Foo</code>, and <code>GroupFoo</code> would match, but <code>foo</code>, <code>F/o/o</code> and <code>Froo</code> would not match.</p>  <p> <code>logGroupNamePattern</code> and <code>logGroupNamePrefix</code> are mutually exclusive. Only one of these parameters can be passed. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logs Client")
    FString logGroupNamePattern;

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
    *  <p>If you are using a monitoring account, set this to <code>True</code> to have the operation return log groups in the accounts listed in <code>accountIdentifiers</code>.</p> <p>If this parameter is set to <code>true</code> and <code>accountIdentifiers</code> contains a null value, the operation returns all log groups in the monitoring account and all log groups in all source accounts that are linked to the monitoring account. </p>  <p> If you specify <code>includeLinkedAccounts</code> in your request, then <code>metricFilterCount</code>, <code>retentionInDays</code>, and <code>storedBytes</code> are not included in the response. </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logs Client")
    bool includeLinkedAccounts = false;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::DescribeLogGroupsRequest toAWS() const {
        Aws::CloudWatchLogs::Model::DescribeLogGroupsRequest awsDescribeLogGroupsRequest;

        for (const FString& elem : this->accountIdentifiers) {
            awsDescribeLogGroupsRequest.AddAccountIdentifiers(TCHAR_TO_UTF8(*elem));
        }

		if (!(this->logGroupNamePrefix.IsEmpty())) {
            awsDescribeLogGroupsRequest.SetLogGroupNamePrefix(TCHAR_TO_UTF8(*this->logGroupNamePrefix));
        }

		if (!(this->logGroupNamePattern.IsEmpty())) {
            awsDescribeLogGroupsRequest.SetLogGroupNamePattern(TCHAR_TO_UTF8(*this->logGroupNamePattern));
        }

		if (!(this->nextToken.IsEmpty())) {
            awsDescribeLogGroupsRequest.SetNextToken(TCHAR_TO_UTF8(*this->nextToken));
        }

        if (!(this->limit == 0)) {
            awsDescribeLogGroupsRequest.SetLimit(this->limit);
        }

        awsDescribeLogGroupsRequest.SetIncludeLinkedAccounts(this->includeLinkedAccounts);

        return awsDescribeLogGroupsRequest;
    }

    bool IsEmpty() const {
        return this->accountIdentifiers.Num() == 0 && this->logGroupNamePrefix.IsEmpty() && this->logGroupNamePattern.IsEmpty() && this->nextToken.IsEmpty() && this->limit == 0 && false;
    }
#endif
};

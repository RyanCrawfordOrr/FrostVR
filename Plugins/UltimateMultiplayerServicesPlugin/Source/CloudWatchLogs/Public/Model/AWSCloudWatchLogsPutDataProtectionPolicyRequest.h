/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, December 2022
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/PutDataProtectionPolicyRequest.h"

#endif

#include "AWSCloudWatchLogsPutDataProtectionPolicyRequest.generated.h"

USTRUCT(BlueprintType)
struct FAWSCloudWatchLogsPutDataProtectionPolicyRequest {
GENERATED_BODY()

    /**
    *  <p>Specify either the log group name or log group ARN.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString logGroupIdentifier;

    /**
    *  <p>Specify the data protection policy, in JSON.</p> <p>This policy must include two JSON blocks:</p> <ul> <li> <p>The first block must include both a <code>DataIdentifer</code> array and an <code>Operation</code> property with an <code>Audit</code> action. The <code>DataIdentifer</code> array lists the types of sensitive data that you want to mask. For more information about the available options, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/logs/mask-sensitive-log-data-types.html">Types of data that you can mask</a>.</p> <p>The <code>Operation</code> property with an <code>Audit</code> action is required to find the sensitive data terms. This <code>Audit</code> action must contain a <code>FindingsDestination</code> object. You can optionally use that <code>FindingsDestination</code> object to list one or more destinations to send audit findings to. If you specify destinations such as log groups, Kinesis Data Firehose streams, and S3 buckets, they must already exist.</p> </li> <li> <p>The second block must include both a <code>DataIdentifer</code> array and an <code>Operation</code> property with an <code>Deidentify</code> action. The <code>DataIdentifer</code> array must exactly match the <code>DataIdentifer</code> array in the first block of the policy.</p> <p>The <code>Operation</code> property with the <code>Deidentify</code> action is what actually masks the data, and it must contain the <code> "MaskConfig": {}</code> object. The <code> "MaskConfig": {}</code> object must be empty.</p> </li> </ul> <p>For an example data protection policy, see the <b>Examples</b> section on this page.</p>  <p>The contents of two <code>DataIdentifer</code> arrays must match exactly.</p> 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString policyDocument;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::PutDataProtectionPolicyRequest toAWS() const {
        Aws::CloudWatchLogs::Model::PutDataProtectionPolicyRequest awsPutDataProtectionPolicyRequest;

        if (!(this->logGroupIdentifier.IsEmpty())) {
            awsPutDataProtectionPolicyRequest.SetLogGroupIdentifier(TCHAR_TO_UTF8(*this->logGroupIdentifier));
        }

        if (!(this->policyDocument.IsEmpty())) {
            awsPutDataProtectionPolicyRequest.SetPolicyDocument(TCHAR_TO_UTF8(*this->policyDocument));
        }

        return awsPutDataProtectionPolicyRequest;
    }

    bool IsEmpty() const {
        return this->logGroupIdentifier.IsEmpty() && this->policyDocument.IsEmpty();
    }
#endif
};

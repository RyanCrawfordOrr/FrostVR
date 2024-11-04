/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/PutResourcePolicyRequest.h"

#endif

#include "PutResourcePolicyRequest.generated.h"

USTRUCT(BlueprintType)
struct FPutResourcePolicyRequest {
GENERATED_BODY()

    /**
    *  <p>Name of the new policy. This parameter is required.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString policyName;

    /**
    *  <p>Details of the new policy, including the identity of the principal that is enabled to put logs to this account. This is formatted as a JSON string. This parameter is required.</p> <p>The following example creates a resource policy enabling the Route 53 service to put DNS query logs in to the specified log group. Replace <code>"logArn"</code> with the ARN of your CloudWatch Logs resource, such as a log group or log stream.</p> <p> <code>{ "Version": "2012-10-17", "Statement": [ { "Sid": "Route53LogsToCloudWatchLogs", "Effect": "Allow", "Principal": { "Service": [ "route53.amazonaws.com" ] }, "Action":"logs:PutLogEvents", "Resource": "logArn" } ] } </code> </p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString policyDocument;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::PutResourcePolicyRequest toAWS() const {
        Aws::CloudWatchLogs::Model::PutResourcePolicyRequest awsPutResourcePolicyRequest;

		if (!(this->policyName.IsEmpty())) {
            awsPutResourcePolicyRequest.SetPolicyName(TCHAR_TO_UTF8(*this->policyName));
        }

		if (!(this->policyDocument.IsEmpty())) {
            awsPutResourcePolicyRequest.SetPolicyDocument(TCHAR_TO_UTF8(*this->policyDocument));
        }

        return awsPutResourcePolicyRequest;
    }

    bool IsEmpty() const {
        return this->policyName.IsEmpty() && this->policyDocument.IsEmpty();
    }
#endif
};

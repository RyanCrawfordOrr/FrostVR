/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/PutDestinationPolicyRequest.h"

#endif

#include "PutDestinationPolicyRequest.generated.h"

USTRUCT(BlueprintType)
struct FPutDestinationPolicyRequest {
GENERATED_BODY()

    /**
    *  <p>A name for an existing destination.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString destinationName;

    /**
    *  <p>An IAM policy document that authorizes cross-account users to deliver their log events to the associated destination. This can be up to 5120 bytes.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString accessPolicy;

    /**
    *  <p>Specify true if you are updating an existing destination policy to grant permission to an organization ID instead of granting permission to individual AWS accounts. Before you update a destination policy this way, you must first update the subscription filters in the accounts that send logs to this destination. If you do not, the subscription filters might stop working. By specifying <code>true</code> for <code>forceUpdate</code>, you are affirming that you have already updated the subscription filters. For more information, see <a href="https://docs.aws.amazon.com/AmazonCloudWatch/latest/logs/Cross-Account-Log_Subscription-Update.html"> Updating an existing cross-account subscription</a> </p> <p>If you omit this parameter, the default of <code>false</code> is used.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    bool forceUpdate = false;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    Aws::CloudWatchLogs::Model::PutDestinationPolicyRequest toAWS() const {
        Aws::CloudWatchLogs::Model::PutDestinationPolicyRequest awsPutDestinationPolicyRequest;

		if (!(this->destinationName.IsEmpty())) {
            awsPutDestinationPolicyRequest.SetDestinationName(TCHAR_TO_UTF8(*this->destinationName));
        }

		if (!(this->accessPolicy.IsEmpty())) {
            awsPutDestinationPolicyRequest.SetAccessPolicy(TCHAR_TO_UTF8(*this->accessPolicy));
        }

        awsPutDestinationPolicyRequest.SetForceUpdate(this->forceUpdate);

        return awsPutDestinationPolicyRequest;
    }

    bool IsEmpty() const {
        return this->destinationName.IsEmpty() && this->accessPolicy.IsEmpty() && false;
    }
#endif
};

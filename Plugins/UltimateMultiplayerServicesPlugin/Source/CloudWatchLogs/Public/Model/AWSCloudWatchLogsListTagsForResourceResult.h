/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, January 2023
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/ListTagsForResourceResult.h"

#endif


#include "AWSCloudWatchLogsListTagsForResourceResult.generated.h"

USTRUCT(BlueprintType)
struct FAWSCloudWatchLogsListTagsForResourceResult {
GENERATED_BODY()

    /**
    *  <p>The list of tags associated with the requested resource.&gt;</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TMap<FString, FString> tags;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FAWSCloudWatchLogsListTagsForResourceResult &fromAWS(const Aws::CloudWatchLogs::Model::ListTagsForResourceResult &awsListTagsForResourceResult) {
        this->tags.Empty();
        for (const auto& elem : awsListTagsForResourceResult.GetTags()) {
            this->tags.Add(UTF8_TO_TCHAR(elem.first.c_str()), UTF8_TO_TCHAR(elem.second.c_str()));
        }

        return *this;
    }
#endif
};

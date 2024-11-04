/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE

#include "aws/logs/model/DescribeLogStreamsResult.h"

#endif

#include "Model/LogStream.h"

#include "DescribeLogStreamsResult.generated.h"

USTRUCT(BlueprintType)
struct FDescribeLogStreamsResult {
GENERATED_BODY()

    /**
    *  <p>The log streams.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    TArray<FLogStream> logStreams;

    /**
    * 
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CloudWatchLogs Client")
    FString nextToken;

#if WITH_CLOUDWATCHLOGSCLIENTSDK && WITH_CORE
public:
    FDescribeLogStreamsResult &fromAWS(const Aws::CloudWatchLogs::Model::DescribeLogStreamsResult &awsDescribeLogStreamsResult) {
        this->logStreams.Empty();
        for (const Aws::CloudWatchLogs::Model::LogStream& elem : awsDescribeLogStreamsResult.GetLogStreams()) {
            this->logStreams.Add(FLogStream().fromAWS(elem));
        }

        this->nextToken = UTF8_TO_TCHAR(awsDescribeLogStreamsResult.GetNextToken().c_str());

        return *this;
    }
#endif
};

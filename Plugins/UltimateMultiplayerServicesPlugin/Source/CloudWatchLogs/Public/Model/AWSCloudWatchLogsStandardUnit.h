/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, December 2022
*/

#pragma once

#include "CoreMinimal.h"

#include "AWSCloudWatchLogsStandardUnit.generated.h"

UENUM(BlueprintType)
enum class EAWSCloudWatchLogsStandardUnit : uint8 {
    NOT_SET        UMETA(DisplayName = "not set"),
    Seconds        UMETA(DisplayName = "seconds"),
    Microseconds        UMETA(DisplayName = "microseconds"),
    Milliseconds        UMETA(DisplayName = "milliseconds"),
    Bytes        UMETA(DisplayName = "bytes"),
    Kilobytes        UMETA(DisplayName = "kilobytes"),
    Megabytes        UMETA(DisplayName = "megabytes"),
    Gigabytes        UMETA(DisplayName = "gigabytes"),
    Terabytes        UMETA(DisplayName = "terabytes"),
    Bits        UMETA(DisplayName = "bits"),
    Kilobits        UMETA(DisplayName = "kilobits"),
    Megabits        UMETA(DisplayName = "megabits"),
    Gigabits        UMETA(DisplayName = "gigabits"),
    Terabits        UMETA(DisplayName = "terabits"),
    Percent        UMETA(DisplayName = "percent"),
    Count        UMETA(DisplayName = "count"),
    Bytes_Second        UMETA(DisplayName = "bytes second"),
    Kilobytes_Second        UMETA(DisplayName = "kilobytes second"),
    Megabytes_Second        UMETA(DisplayName = "megabytes second"),
    Gigabytes_Second        UMETA(DisplayName = "gigabytes second"),
    Terabytes_Second        UMETA(DisplayName = "terabytes second"),
    Bits_Second        UMETA(DisplayName = "bits second"),
    Kilobits_Second        UMETA(DisplayName = "kilobits second"),
    Megabits_Second        UMETA(DisplayName = "megabits second"),
    Gigabits_Second        UMETA(DisplayName = "gigabits second"),
    Terabits_Second        UMETA(DisplayName = "terabits second"),
    Count_Second        UMETA(DisplayName = "count second"),
    None        UMETA(DisplayName = "none"),
};

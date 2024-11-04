/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, December 2022
*/

#pragma once

#include "CoreMinimal.h"

#include "AWSCloudWatchLogsDataProtectionStatus.generated.h"

UENUM(BlueprintType)
enum class EAWSCloudWatchLogsDataProtectionStatus : uint8 {
    NOT_SET        UMETA(DisplayName = "not set"),
    ACTIVATED        UMETA(DisplayName = "activated"),
    DELETED        UMETA(DisplayName = "deleted"),
    ARCHIVED        UMETA(DisplayName = "archived"),
    DISABLED        UMETA(DisplayName = "disabled"),
};

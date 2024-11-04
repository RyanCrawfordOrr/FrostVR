/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, August 2020
*/

#pragma once

#include "CoreMinimal.h"

#include "QueryStatus.generated.h"

UENUM(BlueprintType)
enum class EAWSQueryStatus : uint8 {
    NOT_SET        UMETA(DisplayName = "not set"),
    Scheduled        UMETA(DisplayName = "scheduled"),
    Running        UMETA(DisplayName = "running"),
    Complete        UMETA(DisplayName = "complete"),
    Failed        UMETA(DisplayName = "failed"),
    Cancelled        UMETA(DisplayName = "cancelled"),
    Timeout        UMETA(DisplayName = "timeout"),
    Unknown        UMETA(DisplayName = "unknown"),
};

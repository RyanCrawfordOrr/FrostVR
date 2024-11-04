/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#include "ExportTaskStatusCode.generated.h"

UENUM(BlueprintType)
enum class EAWSExportTaskStatusCode : uint8 {
    NOT_SET        UMETA(DisplayName = "not set"),
    CANCELLED        UMETA(DisplayName = "cancelled"),
    COMPLETED        UMETA(DisplayName = "completed"),
    FAILED        UMETA(DisplayName = "failed"),
    PENDING        UMETA(DisplayName = "pending"),
    PENDING_CANCEL        UMETA(DisplayName = "pending cancel"),
    RUNNING        UMETA(DisplayName = "running"),
};

/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, September 2020
*/

#pragma once

#include "CoreMinimal.h"

#include "AWSDistribution.generated.h"

UENUM(BlueprintType)
enum class EAWSDistribution : uint8 {
    NOT_SET        UMETA(DisplayName = "not set"),
    Random        UMETA(DisplayName = "random"),
    ByLogStream        UMETA(DisplayName = "bylogstream"),
};

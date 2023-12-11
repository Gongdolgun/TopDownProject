#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraShake.h"
#include "CS_Base.generated.h"

UCLASS()
class TOPVIEWPROJECT_API UCS_Base : public UMatineeCameraShake
{
	GENERATED_BODY()

public:
	UCS_Base();
};

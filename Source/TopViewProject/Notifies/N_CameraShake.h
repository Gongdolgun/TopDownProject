#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "N_CameraShake.generated.h"

UCLASS()
class TOPVIEWPROJECT_API UN_CameraShake : public UAnimNotify
{
	GENERATED_BODY()

public:
	FString GetNotifyName_Implementation() const override;

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UMatineeCameraShake> CameraShake;

	UPROPERTY(EditAnywhere)
		float ShakeScale;
};

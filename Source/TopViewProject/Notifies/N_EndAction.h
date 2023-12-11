#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "N_EndAction.generated.h"

UCLASS()
class TOPVIEWPROJECT_API UN_EndAction : public UAnimNotify
{
	GENERATED_BODY()

	FString GetNotifyName_Implementation() const override;

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
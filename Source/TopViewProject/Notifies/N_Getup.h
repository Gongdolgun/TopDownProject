#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "N_Getup.generated.h"

UCLASS()
class TOPVIEWPROJECT_API UN_Getup : public UAnimNotify
{
	GENERATED_BODY()

	FString GetNotifyName_Implementation() const override;

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};

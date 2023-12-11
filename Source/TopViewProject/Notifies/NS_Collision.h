#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Interfaces/IDamage.h"
#include "NS_Collision.generated.h"

UCLASS()
class TOPVIEWPROJECT_API UNS_Collision : public UAnimNotifyState
{
	GENERATED_BODY()

	FString GetNotifyName_Implementation() const override;

	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditAnywhere, Category = "Attack Type")
		EAttackType AttackType;

	UPROPERTY(EditAnywhere, Category = "Attack Type")
		FVector LaunchRate;

	UPROPERTY(EditAnywhere)
		float DamagePercent;
};
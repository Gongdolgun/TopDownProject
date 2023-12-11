#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/CFeetComponent.h"
#include "CAnimInstance.generated.h"

UCLASS()
class TOPVIEWPROJECT_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		float Pitch;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		float Direction;

public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	class ACPlayer* OwnerCharacter;

private:
	FRotator PrevRotation;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InverseKinemetics")
		bool bFeet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InverseKinemetics")
		FFeetData FeetData;
};

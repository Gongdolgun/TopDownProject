#pragma once

#include "CoreMinimal.h"
#include "Enemy/CEnemy.h"
#include "CEnemy_Lich.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACEnemy_Lich : public ACEnemy
{
	GENERATED_BODY()

public:
	ACEnemy_Lich();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void DoRagDoll() override;

public:
	UPROPERTY(EditAnywhere)
		UAnimMontage* DeadAnim;
};

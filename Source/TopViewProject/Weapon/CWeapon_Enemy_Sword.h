#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon_Enemy.h"
#include "CWeapon_Enemy_Sword.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACWeapon_Enemy_Sword : public ACWeapon_Enemy
{
	GENERATED_BODY()

public:
	ACWeapon_Enemy_Sword();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* Box_Collision;
};

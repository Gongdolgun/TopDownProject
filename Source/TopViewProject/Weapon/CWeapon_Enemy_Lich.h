#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon_Enemy.h"
#include "CWeapon_Enemy_Lich.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACWeapon_Enemy_Lich : public ACWeapon_Enemy
{
	GENERATED_BODY()

public:
	ACWeapon_Enemy_Lich();

protected:
	void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
		class UBoxComponent* Box_Collision;
};

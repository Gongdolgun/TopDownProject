#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CWeaponComponent_Enemy.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPVIEWPROJECT_API UCWeaponComponent_Enemy : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCWeaponComponent_Enemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void DoAction();
	void End_DoAction();
	void OnCollision();
	void OffCollision();

public:
	UPROPERTY(EditAnywhere, Category = "Weapon")
		TSubclassOf<class ACWeapon_Enemy> WeaponClass;

private:
	class ACEnemy* Owner;
		
public:
	ACWeapon_Enemy* Weapon;
};

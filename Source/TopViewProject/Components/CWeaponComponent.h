#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPVIEWPROJECT_API UCWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCWeaponComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void DoAction();
	void Begin_DoAction();
	void End_DoAction();

public:
	void Q_Skill();
	void W_Skill();
	void E_Skill();
	void R_Skill();

	void A_Skill();
	void S_Skill();
	void D_Skill();
	void F_Skill();

	void V_Skill();

public:
	UPROPERTY(EditAnywhere, Category = "Weapon")
		TSubclassOf<class ACWeapon> WeaponClass;

private:
	class ACPlayer* Owner;

public:
	ACWeapon* Weapon;
};

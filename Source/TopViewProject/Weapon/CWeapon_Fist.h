#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon.h"
#include "CWeapon_Fist.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACWeapon_Fist : public ACWeapon
{
	GENERATED_BODY()

public:
	ACWeapon_Fist();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere)
	class USphereComponent* Sphere_R;

	UPROPERTY(EditAnywhere)
	class USphereComponent* Sphere_L;

	UPROPERTY(EditAnywhere)
		class USphereComponent* Sphere_Leg_R;

	UPROPERTY(EditAnywhere)
		class USphereComponent* Sphere_Leg_L;

	UPROPERTY(EditAnywhere, Category = "SkillMontage")
		UAnimMontage* TakeDown_Montage;

	UPROPERTY(EditAnywhere, Category = "SkillMontage")
		UAnimMontage* BlastFormation_Montage;

	UPROPERTY(EditAnywhere, Category = "SkillMontage")
		UAnimMontage* ContinuosPush_Montage;

	UPROPERTY(EditAnywhere, Category = "SkillMontage")
		UAnimMontage* Fury_Montage;

	UPROPERTY(EditAnywhere, Category = "SkillMontage")
		UAnimMontage* Tornado_Montage;

	UPROPERTY(EditAnywhere, Category = "SkillMontage")
		UAnimMontage* OnePunch_Montage;

	UPROPERTY(EditAnywhere, Category = "SpiritBomb_Montage")
		UAnimMontage* Launch_Montage;

	UPROPERTY(EditAnywhere, Category = "SpiritBomb_Montage")
		UAnimMontage* SpiritBomb_Start_Montage;

	UPROPERTY(EditAnywhere, Category = "SpiritBomb_Montage")
		UAnimMontage* SpiritBomb_End_Montage;

public:
	void Skill_TakeDown() override;
	void Skill_BlastFormation() override;
	void Skill_ContinuousPush() override;
	void Skill_Fury() override;
	void Skill_Tornado() override;
	void Skill_OnePunch() override;

	void Skill_SpiritBomb() override;

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACBlastFormation> blastFormation;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACSpritBomb> BP_SpiritBomb;

private:
	class UGameInstance_Test* GameInstance;
};
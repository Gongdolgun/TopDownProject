#include "Components/CWeaponComponent.h"
#include "Weapon/CWeapon.h"
#include "Player/CPlayer.h"

UCWeaponComponent::UCWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACPlayer>(GetOwner());

	FActorSpawnParameters params;
	params.Owner = Owner;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if(!!WeaponClass)
	{
		Weapon = Owner->GetWorld()->SpawnActor<ACWeapon>(WeaponClass, params);
	}
}

void UCWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCWeaponComponent::DoAction()
{
	Weapon->DoAction();
}

void UCWeaponComponent::Begin_DoAction()
{
	Weapon->Begin_DoAction();
}

void UCWeaponComponent::End_DoAction()
{
	Weapon->End_DoAction();
}

void UCWeaponComponent::Q_Skill()
{
	Weapon->Skill_TakeDown();
}

void UCWeaponComponent::W_Skill()
{
	Weapon->Skill_BlastFormation();
}

void UCWeaponComponent::E_Skill()
{
	Weapon->Skill_ContinuousPush();
}

void UCWeaponComponent::R_Skill()
{
	Weapon->Skill_Fury();
}

void UCWeaponComponent::A_Skill()
{
	Weapon->Skill_Tornado();
}

void UCWeaponComponent::S_Skill()
{
	Weapon->Skill_OnePunch();
}

void UCWeaponComponent::D_Skill()
{
}

void UCWeaponComponent::F_Skill()
{
}

void UCWeaponComponent::V_Skill()
{
	Weapon->Skill_SpiritBomb();
}


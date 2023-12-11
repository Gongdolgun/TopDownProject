#include "Components/CWeaponComponent_Enemy.h"

#include "Enemy/CEnemy.h"
#include "Weapon/CWeapon_Enemy.h"

UCWeaponComponent_Enemy::UCWeaponComponent_Enemy()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCWeaponComponent_Enemy::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACEnemy>(GetOwner());

	FActorSpawnParameters params;
	params.Owner = Owner;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (!!WeaponClass)
	{
		Weapon = Owner->GetWorld()->SpawnActor<ACWeapon_Enemy>(WeaponClass, params);
	}
}


void UCWeaponComponent_Enemy::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCWeaponComponent_Enemy::DoAction()
{
	Weapon->DoAction();
}

void UCWeaponComponent_Enemy::End_DoAction()
{
	Weapon->End_DoAction();
}

void UCWeaponComponent_Enemy::OnCollision()
{
	Weapon->OnCollision();
}

void UCWeaponComponent_Enemy::OffCollision()
{
	Weapon->OffCollision();
}

#include "Enemy/CEnemy_Lich.h"
#include "Global.h"
#include "Components/CWeaponComponent.h"
#include "Components/CAIBehaviorComponent.h"

ACEnemy_Lich::ACEnemy_Lich()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACEnemy_Lich::BeginPlay()
{
	Super::BeginPlay();
}

void ACEnemy_Lich::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACEnemy_Lich::DoRagDoll()
{
	// Super::DoRagDoll();

	PlayAnimMontage(DeadAnim, 0.7f);
}

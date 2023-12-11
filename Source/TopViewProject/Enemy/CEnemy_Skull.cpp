#include "Enemy/CEnemy_Skull.h"
#include "Global.h"
#include "Components/CWeaponComponent.h"
#include "Components/CAIBehaviorComponent.h"

ACEnemy_Skull::ACEnemy_Skull()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACEnemy_Skull::BeginPlay()
{
	Super::BeginPlay();
}

void ACEnemy_Skull::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

#include "CChaosController.h"
#include "Global.h"

ACChaosController::ACChaosController()
{
 	PrimaryActorTick.bCanEverTick = true;

}

void ACChaosController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACChaosController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACChaosController::DisCountEnemy()
{
	EnemyCount--;

	if(EnemyCount < 5 && !IsGateOpen)
	{
		SpawnEnemy();
	}
}

void ACChaosController::CountEnemy()
{
	EnemyCount++;
}

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CChaosController.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACChaosController : public AActor
{
	GENERATED_BODY()
	
public:	
	ACChaosController();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void CountEnemy();
	void DisCountEnemy();

public:
	UFUNCTION(BlueprintImplementableEvent)
		void SpawnEnemy();

public:
	UPROPERTY(VisibleAnywhere)
		int EnemyCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool IsGateOpen;

};
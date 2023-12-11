#pragma once

#include "CoreMinimal.h"
#include "Enemy/CEnemy.h"
#include "CEnemy_Boss.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACEnemy_Boss : public ACEnemy
{
	GENERATED_BODY()

public:
	ACEnemy_Boss();

protected:
	virtual void BeginPlay() override;
	virtual void BaseAttack(EAttackType InAttackType, AActor* Attacker, float PlayRate, float Damage, FVector LaunchRate) override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* CubeParticle;

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* AuraParticle;

public:
	UFUNCTION(BlueprintImplementableEvent)
		void GameFinish();
};
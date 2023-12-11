#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "CBlastFormation.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACBlastFormation : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBlastFormation();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
public:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* Layer0;

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* Layer1_1;

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* Layer1_2;

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* Layer1_3;

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* Layer2_1;

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* Layer2_2;

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* Layer2_3;

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* Layer2_4;

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* Layer2_5;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* Box_Layer0;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* Box_Layer1;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* Box_Layer2;

public:
	UPROPERTY(EditAnywhere)
	float DamagePercent = 500.f;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	TArray<UActorComponent*> Collisions;
	float time = 0;
};

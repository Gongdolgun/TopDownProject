#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CSpritBomb.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACSpritBomb : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSpritBomb();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Sphere1;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Sphere2;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Sphere3;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Sphere4;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Line1;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Line2;

	UPROPERTY(EditAnywhere)
		USphereComponent* Collision;

	UPROPERTY(EditAnywhere)
		UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere)
		UTimelineComponent* Timeline;

	UPROPERTY(EditAnywhere)
		UCurveFloat* Curve;

	UPROPERTY(EditAnywhere)
		UNiagaraSystem* Ground_Effect;

public:
	UFUNCTION()
		void Timeline_Func(float Output);

	UFUNCTION()
		void Timeline_End();

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	UPROPERTY(EditAnywhere)
		float Scale = 1.6f;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACSpiritBomb_Explosion> BP_SpiritBomb_Explosion;

public:
	UPROPERTY(EditAnywhere, Category = "CameraShake")
		TSubclassOf<UMatineeCameraShake> CS_Base;

	UPROPERTY(EditAnywhere, Category = "CameraShake")
		float CS_Scale;
};
#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "CSpiritBomb_Explosion.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACSpiritBomb_Explosion : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSpiritBomb_Explosion();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

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
		UTimelineComponent* Timeline;

	UPROPERTY(EditAnywhere)
		URotatingMovementComponent* RotatingMovement;

	UPROPERTY(EditAnywhere)
		UCurveFloat* Curve;

	UPROPERTY(EditAnywhere)
		UNiagaraSystem* Smoke;

	UPROPERTY(EditAnywhere)
		USphereComponent* Collision;

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

public:
	UPROPERTY(EditAnywhere, Category = "CameraShake")
		TSubclassOf<UMatineeCameraShake> CS_Base;

	UPROPERTY(EditAnywhere, Category = "CameraShake")
		float CS_Scale;
};

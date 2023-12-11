#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Interfaces/IDamage.h"
#include "CTornado.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACTornado : public AActor
{
	GENERATED_BODY()
	
public:	
	ACTornado();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Tornado;

	UPROPERTY(EditAnywhere)
		class UCapsuleComponent* Collision;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UMatineeCameraShake> CameraShake;

	UPROPERTY(EditAnywhere)
		float ShakeScale;

	UPROPERTY(EditAnywhere)
		float LaunchScale;

private:
	TArray<IIDamage*> HitActors;
	FTimerHandle TimerHandle_Hit;
	FTimerHandle TimerHandle_Destroy;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

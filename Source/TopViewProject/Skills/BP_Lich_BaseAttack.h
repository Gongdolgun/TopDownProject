#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_Lich_BaseAttack.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ABP_Lich_BaseAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	ABP_Lich_BaseAttack();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		class USphereComponent* Collision;

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* Attack;

	UPROPERTY(EditAnywhere)
		class UProjectileMovementComponent* ProjectileMovement;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};

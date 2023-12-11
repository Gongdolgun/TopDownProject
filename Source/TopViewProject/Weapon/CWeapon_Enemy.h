#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon_Enemy.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACWeapon_Enemy : public AActor
{
	GENERATED_BODY()
	
public:	
	ACWeapon_Enemy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

protected:
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Mesh;

public:
	TArray<AActor*> HitActors;
	TArray<UActorComponent*> Collisions;
	float Damage = 0;

protected:
	class ACEnemy* Owner;

protected:
	UPROPERTY(EditAnywhere, Category = "Action_Montage")
		class UAnimMontage* BaseAttack_Montage;

public:
	UFUNCTION()
		void DoAction();

	UFUNCTION()
		void OnCollision();

	UFUNCTION()
		void OffCollision();

	UFUNCTION()
		void End_DoAction();

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/MovementComponent.h"
#include "Interfaces/IDamage.h"
#include "CWeapon.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACWeapon();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

protected:
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Mesh2;

	UPROPERTY(EditAnywhere, Category = "BaseAttack")
		TArray<class UAnimMontage*> BaseAttack;


public:
	UPROPERTY(EditAnywhere, Category = "CameraShake")
		TSubclassOf<UMatineeCameraShake> CS_Base;

	UPROPERTY(EditAnywhere, Category = "CameraShake")
		TArray<float> CS_Scale;
		
	
public:
	UFUNCTION()
		void DoAction();

	UFUNCTION()
		void Begin_DoAction();

	UFUNCTION()
		void End_DoAction();

	UFUNCTION()
		void OnCollision();

	UFUNCTION()
		void OffCollision();

	UFUNCTION()
		void CameraShake(TSubclassOf<UMatineeCameraShake> InCameraShake, float InScale);

public:
	int MontageNum = 0;
	FVector LaunchRate;
	bool comboEnable = false;
	bool combo;
	TArray<AActor*> HitActors;
	TArray<UActorComponent*> Collisions;
	EAttackType AttackType;
	float Damage = 0;

protected:
	class ACPlayer* Owner;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual void Skill_TakeDown();
	virtual void Skill_BlastFormation();
	virtual void Skill_ContinuousPush();
	virtual void Skill_Fury();
	virtual void Skill_Tornado();
	virtual void Skill_OnePunch();

	virtual void Skill_SpiritBomb();
};

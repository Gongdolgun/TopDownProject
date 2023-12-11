#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/IDamage.h"
#include "Player/CPlayer.h"
#include "Components/WidgetComponent.h"
#include "CEnemy.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACEnemy : public ACharacter, public IIDamage
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		uint8 TeamID = 2;

public:
	UPROPERTY(VisibleDefaultsOnly)
		class UCAIBehaviorComponent* Behavior;

	UPROPERTY(VisibleAnywhere)
		class UCWeaponComponent_Enemy* WeaponComponent;

public:
	FORCEINLINE uint8 GetTeamID() { return TeamID; }
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }


public:
	ACEnemy();
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	virtual void BaseAttack(EAttackType InAttackType, AActor* Attacker, float PlayRate, float Damage, FVector LaunchRate) override;

	virtual void Landed(const FHitResult& Hit) override;

public:
	UPROPERTY(EditAnywhere, Category = "HitReaction")
		UAnimMontage* StaggerMontage;

	UPROPERTY(EditAnywhere, Category = "HitReaction")
		UAnimMontage* KnockDownMontage;

	UPROPERTY(EditAnywhere)
		UWidgetComponent* WDG_HPBar;

	UPROPERTY(EditAnywhere)
		UWidgetComponent* WDG_Damage;

	UPROPERTY(EditAnywhere)
		UTimelineComponent* Timeline;

	UPROPERTY(EditAnywhere)
		UCurveFloat* Curve;

public:
	UPROPERTY(EditAnywhere)
		bool Follow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float HP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Max_HP;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> DamageWidget;

public:
	ACPlayer* target;
	bool IsDead = false;
	bool isHitted = false;

	float minDamage;
	float maxDamage;
	float FinalDamage;

	//timerhandle

public:
	class ACChaosController* ChaosController;
	class UGameInstance_Test* GameInstance;


public:
	UFUNCTION()
		void Appearance(float Output);

	UFUNCTION()
		virtual void DoRagDoll();

public:
	float Cal_Damage(float percent);
};
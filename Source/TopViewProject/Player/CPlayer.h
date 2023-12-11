#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Interfaces/IDamage.h"
#include "GenericTeamAgentInterface.h"
#include "Components/WidgetComponent.h"
#include "CPlayer.generated.h"

UCLASS(Blueprintable)
class ACPlayer : public ACharacter, public IIDamage, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Team")
		uint8 TeamID = 1;

public:
	ACPlayer();

	virtual void BeginPlay() override;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(TeamID); }

	virtual void BaseAttack(EAttackType InAttackType, AActor* Attacker, float PlayRate, float Damage, FVector LaunchRate) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return Camera; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return SpringArm; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

public:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;


	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;


private:
	FVector ActorLocation;
	bool bZooming = false;
	float CameraHeight = 500.f;
	float TargetArmLength = 1000.f;

	float minDamage;
	float maxDamage;
	float FinalDamage;

	class UGameInstance_Test* gameInstance;

public:
	bool bCritical;
	float CriticalRate = 30;

public:
	UPROPERTY(EditAnywhere, Category = "Sprint")
		float SprintDistance;

	UPROPERTY(EditAnywhere, Category = "HitReaction")
		UAnimMontage* StaggerMontage;

	UPROPERTY(EditAnywhere, Category = "HitReaction")
		UAnimMontage* KnockDownMontage;

public:
	UPROPERTY(EditAnywhere, Category = "Curves")
		UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere, Category = "Curves")
		UCurveFloat* ZoomCurve;

	UPROPERTY(VisibleAnywhere)
		UAnimMontage* SprintMotion;

	UPROPERTY(VisibleAnywhere)
		UNiagaraSystem* SprintParticle;

	UPROPERTY(VisibleAnywhere)
		UNiagaraSystem* SprintParticle2;

	UPROPERTY(EditAnywhere)
		UNiagaraComponent* AfterEffect;

	UPROPERTY(EditAnywhere)
		UWidgetComponent* WDG_Damage;

	UPROPERTY(BlueprintReadWrite)
		class UCUserWidget_Chaos* WDG_Chaos;

public:
	UPROPERTY(VisibleAnywhere)
		class UTimelineComponent* Timeline;

	UPROPERTY(VisibleAnywhere)
		class UTimelineComponent* Timeline2;

	UPROPERTY(VisibleAnywhere)
		class UTimelineComponent* Timeline3;

	UPROPERTY(VisibleAnywhere)
		class UTimelineComponent* Timeline4;

public:
	UPROPERTY(VisibleAnywhere)
		class UCWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere)
		class UCStateComponent* StateComponent;

	UPROPERTY(VisibleAnywhere)
		class UCMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* ClickParticle;

public:
	void OnSprint();
	void OnZoomIn();
	void OnZoomOut();
	void Stop();
	void ChangeRotationToCursor();
	float Cal_Damage(float percent);
	void SetMP(float MPRate);

private:
	UFUNCTION()
		void BeginSprint(float Output);

	UFUNCTION()
		void BeginZoomIn(float Output);

	UFUNCTION()
		void BeginZoomOut(float Output);

	UFUNCTION()
		void ChangeRotationToCursor(float Output);

	UFUNCTION()
		void DoAction();

};

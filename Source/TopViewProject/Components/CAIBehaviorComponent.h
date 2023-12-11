#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CAIBehaviorComponent.generated.h"

UENUM()
enum class ESpeedType : uint8
{
	Walk = 0, Run, Sprint, Max,
};

UENUM(BlueprintType)
enum class EAIStateType : uint8
{
	Wait = 0, Approach, Action, Patrol, Hitted, Avoid, Dead, Max,
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAIStateTypeChanged, EAIStateType, InPrevType, EAIStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPVIEWPROJECT_API UCAIBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Key")
		FName AIStateTypeKey = "AIState";

	UPROPERTY(EditAnywhere, Category = "Key")
		FName TargetKey = "Target";

	UPROPERTY(EditAnywhere, Category = "Key")
		FName PatrolLocationKey = "Patrol_Location";

	UPROPERTY(EditAnywhere, Category = "Key")
		FName LocationKey = "Location";

private:
	UPROPERTY(EditAnywhere, Category = "Speed")
		float Speed[(int32)ESpeedType::Max] = { 200, 400, 600 };

public:
	FORCEINLINE float GetWalkSpeed() { return Speed[(int32)ESpeedType::Walk]; }
	FORCEINLINE float GetRunSpeed() { return Speed[(int32)ESpeedType::Run]; }
	FORCEINLINE float GetSprintSpeed() { return Speed[(int32)ESpeedType::Sprint]; }

private:
	EAIStateType GetType();

public:
	bool IsWaitMode();
	bool IsApproachMode();
	bool IsActionMode();
	bool IsPatrolMode();
	bool IsHittedMode();
	bool IsAvoidMode();
	bool IsDeadMode();

public:
	void SetSpeed(ESpeedType InType);

public:
	UCAIBehaviorComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE void SetBlackboard(class UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }

public:
	class ACharacter* GetTarget();

public:
	FVector GetPatrolLocation();
	FVector GetLocation();
	void SetPatrolLocation(const FVector& InLocation);

public:
	void SetWaitMode();
	void SetApproachMode();
	void SetActionMode();
	void SetPatrolMode();
	void SetHittedMode();
	void SetAvoidMode();
	void SetDeadMode();
	void SetTarget(AActor* InActor);

private:
	void ChangeType(EAIStateType InType);

public:
	FAIStateTypeChanged OnAIStateTypeChanged;

private:
	class UBlackboardComponent* Blackboard;

private:
	class ACharacter* OwnerCharacter;
};

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM()
enum class EStateType : uint8
{
	Idle = 0, Action, Skill
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPVIEWPROJECT_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStateComponent();

public:
	FORCEINLINE bool IsIdleMode() { return Type == EStateType::Idle; }
	FORCEINLINE bool IsActionMode() { return Type == EStateType::Action; }
	FORCEINLINE bool IsSkillMode() { return Type == EStateType::Skill; }

protected:
	virtual void BeginPlay() override;

public:
	void SetIdleMode();
	void SetActionMode();
	void SetSkillMode();

public:
	void ChangeType(EStateType InType);

private:
	EStateType Type;
};

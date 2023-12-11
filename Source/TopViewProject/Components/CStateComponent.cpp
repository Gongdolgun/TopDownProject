#include "Components/CStateComponent.h"

UCStateComponent::UCStateComponent()
{
	
}

void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCStateComponent::SetIdleMode()
{
	ChangeType(EStateType::Idle);
}

void UCStateComponent::SetActionMode()
{
	ChangeType(EStateType::Action);
}

void UCStateComponent::SetSkillMode()
{
	ChangeType(EStateType::Skill);
}

void UCStateComponent::ChangeType(EStateType InType)
{
	Type = InType;
}

#include "Components/CMovementComponent.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"

UCMovementComponent::UCMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UCMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCMovementComponent::EnableMove()
{
	bCanMove = true;
}

void UCMovementComponent::DisableMove()
{
	bCanMove = false;
}

void UCMovementComponent::EnableSprint()
{
	bCanSprint = true;
}

void UCMovementComponent::DisableSprint()
{
	bCanSprint = false;
}

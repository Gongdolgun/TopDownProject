#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPVIEWPROJECT_API UCMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCMovementComponent();

	FORCEINLINE bool IsEnableMove() { return bCanMove; }
	FORCEINLINE bool IsEnableSprint() { return bCanSprint; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void EnableMove();
	void DisableMove();
	void EnableSprint();
	void DisableSprint();

private:
	bool bCanMove = true;
	bool bCanSprint = true;
};

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_AI.generated.h"

UCLASS()
class TOPVIEWPROJECT_API UCBTService_AI : public UBTService
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Action")
		float ActionRange = 150;

public:
	UCBTService_AI();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};

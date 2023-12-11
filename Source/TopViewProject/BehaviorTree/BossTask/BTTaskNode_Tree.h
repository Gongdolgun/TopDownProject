#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Tree.generated.h"

UCLASS()
class TOPVIEWPROJECT_API UBTTaskNode_Tree : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_Tree();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACBoss_Tree> Tree;
};

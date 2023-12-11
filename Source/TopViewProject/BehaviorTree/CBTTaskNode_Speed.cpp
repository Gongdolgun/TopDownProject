#include "BehaviorTree/CBTTaskNode_Speed.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Enemy/AIController/CAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

UCBTTaskNode_Speed::UCBTTaskNode_Speed()
{
	NodeName = "Speed";
}

EBTNodeResult::Type UCBTTaskNode_Speed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy* ai = Cast<ACEnemy>(controller->GetPawn());
	UCAIBehaviorComponent* behavior = CHelpers::GetComponent<UCAIBehaviorComponent>(ai);

	behavior->SetSpeed(Type);

	return EBTNodeResult::Succeeded;
}
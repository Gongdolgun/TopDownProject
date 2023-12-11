#include "BehaviorTree/CBTTaskNode_Action.h"
#include "Global.h"
#include "Components/SplineComponent.h"
#include "Components/CAIBehaviorComponent.h"
#include "Components/CWeaponComponent_Enemy.h"
#include "Enemy/CEnemy.h"
#include "Enemy/AIController/CAIController.h"

UCBTTaskNode_Action::UCBTTaskNode_Action()
{
	bNotifyTick = true;

	NodeName = "Action";
}

EBTNodeResult::Type UCBTTaskNode_Action::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy* ai = Cast<ACEnemy>(controller->GetPawn());
	UCAIBehaviorComponent* behavior = CHelpers::GetComponent<UCAIBehaviorComponent>(ai);

	WeaponComponent = CHelpers::GetComponent<UCWeaponComponent_Enemy>(ai);
	CheckNullResult(WeaponComponent, EBTNodeResult::Failed);

	controller->StopMovement();
	WeaponComponent->DoAction();

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Action::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	
}

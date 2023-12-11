#include "BehaviorTree/BossTask/BTTaskNode_Tree.h"
#include "Global.h"
#include "Components/CAIBehaviorComponent.h"
#include "Enemy/CEnemy.h"
#include "Enemy/AIController/CAIController.h"
#include "Skills/CBoss_Tree.h"

UBTTaskNode_Tree::UBTTaskNode_Tree()
{
	bNotifyTick = true;

	NodeName = "Tree";
}

EBTNodeResult::Type UBTTaskNode_Tree::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy* ai = Cast<ACEnemy>(controller->GetPawn());
	UCAIBehaviorComponent* behavior = CHelpers::GetComponent<UCAIBehaviorComponent>(ai);

	FActorSpawnParameters param;
	param.Owner = ai;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if(!!Tree)
	{
		GetWorld()->SpawnActor<ACBoss_Tree>(Tree, behavior->GetLocation(), FRotator::ZeroRotator, param);
	}


	return EBTNodeResult::Succeeded;
}

void UBTTaskNode_Tree::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

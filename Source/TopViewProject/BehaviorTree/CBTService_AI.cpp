#include "BehaviorTree/CBTService_AI.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Enemy/AIController/CAIController.h"
#include "Enemy/CEnemy.h"
#include "Components/CStateComponent.h"
#include "Components/CAIBehaviorComponent.h"

UCBTService_AI::UCBTService_AI()
{
	NodeName = "Melee";

	Interval = 0.1f;
	RandomDeviation = 0.0f;
}

void UCBTService_AI::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy* ai = Cast<ACEnemy>(controller->GetPawn());
	UCAIBehaviorComponent* aiState = CHelpers::GetComponent<UCAIBehaviorComponent>(ai);


	ACharacter* target = aiState->GetTarget();
	if (target == nullptr && !aiState->IsActionMode())
	{
		aiState->SetPatrolMode();

		return;
	}

	float distance = ai->GetDistanceTo(target);
	if (distance < ActionRange)
	{
		aiState->SetActionMode();

		return;
	}

	if(!aiState->IsActionMode())
		aiState->SetApproachMode();
}

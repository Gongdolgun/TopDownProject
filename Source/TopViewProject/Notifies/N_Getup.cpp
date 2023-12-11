#include "Notifies/N_Getup.h"
#include "GameFramework/Character.h"
#include "Global.h"
#include "Components/CAIBehaviorComponent.h"
#include "Components/CapsuleComponent.h"
#include "Enemy/CEnemy.h"

FString UN_Getup::GetNotifyName_Implementation() const
{
	return "Getup";
}

void UN_Getup::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACharacter* Owner = Cast<ACharacter>(MeshComp->GetOwner());
	CheckNull(Owner);

	Owner->GetCapsuleComponent()->SetCollisionProfileName("Pawn");

	ACEnemy* enemy = Cast<ACEnemy>(Owner);
	if(!!enemy)
	{
		enemy->Behavior->SetWaitMode();
	}
}

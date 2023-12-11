#include "Notifies/N_AfterEffect.h"
#include "Player/CPlayer.h"

FString UN_AfterEffect::GetNotifyName_Implementation() const
{
	return "AfterEffect";
}

void UN_AfterEffect::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ACPlayer* Owner = Cast<ACPlayer>(MeshComp->GetOwner());

	if (!!Owner)
	{
		Owner->AfterEffect->Activate();
	}
}

void UN_AfterEffect::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ACPlayer* Owner = Cast<ACPlayer>(MeshComp->GetOwner());

	if (!!Owner)
	{
		Owner->AfterEffect->Deactivate();
	}
}
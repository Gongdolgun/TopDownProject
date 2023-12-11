#include "Notifies/N_CameraShake.h"
#include "Global.h"

FString UN_CameraShake::GetNotifyName_Implementation() const
{
	return "CameraShake";
}

void UN_CameraShake::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	CheckNull(MeshComp->GetOwner()->GetWorld()->GetFirstPlayerController());

	if(!!CameraShake)
	{
		if (!!MeshComp->GetOwner()->GetWorld())
			MeshComp->GetOwner()->GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CameraShake, ShakeScale);
	}
}

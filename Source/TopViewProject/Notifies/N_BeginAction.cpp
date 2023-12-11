#include "Notifies/N_BeginAction.h"
#include "Components/CWeaponComponent.h"
#include "Global.h"
#include "Components/CMovementComponent.h"

FString UN_BeginAction::GetNotifyName_Implementation() const
{
	return "BeginAction";
}

void UN_BeginAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCWeaponComponent* WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(WeaponComponent);

	WeaponComponent->Begin_DoAction();
}
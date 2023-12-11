#include "Notifies/N_EndAction.h"
#include "Components/CWeaponComponent.h"
#include "Global.h"
#include "Components/CMovementComponent.h"

FString UN_EndAction::GetNotifyName_Implementation() const
{
	
	return "End Action";
}

void UN_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCWeaponComponent* WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(WeaponComponent);

	UCMovementComponent* MovementComponent = CHelpers::GetComponent<UCMovementComponent>(MeshComp->GetOwner());
	CheckNull(MovementComponent);

	WeaponComponent->End_DoAction();
	MovementComponent->EnableMove();
}

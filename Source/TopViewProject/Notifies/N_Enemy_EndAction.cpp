#include "Notifies/N_Enemy_EndAction.h"
#include "Components/CWeaponComponent_Enemy.h"
#include "Global.h"

FString UN_Enemy_EndAction::GetNotifyName_Implementation() const
{
	return "Enemy_EndAction";
}

void UN_Enemy_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCWeaponComponent_Enemy* weaponComponent = CHelpers::GetComponent<UCWeaponComponent_Enemy>(MeshComp->GetOwner());
	CheckNull(weaponComponent);

	weaponComponent->End_DoAction();
}

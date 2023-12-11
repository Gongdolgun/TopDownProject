#include "Notifies/NS_Combo.h"
#include "Components/CWeaponComponent.h"
#include "Components/CMovementComponent.h"
#include "Global.h"
#include "Weapon/CWeapon.h"

FString UNS_Combo::GetNotifyName_Implementation() const
{
	return "Combo";
}

void UNS_Combo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCWeaponComponent* WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(WeaponComponent);

	WeaponComponent->Weapon->comboEnable = true;
}

void UNS_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCWeaponComponent* WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(WeaponComponent);

	WeaponComponent->Weapon->comboEnable = false;
}

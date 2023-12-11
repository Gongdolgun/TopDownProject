#include "Notifies/NS_Collision.h"
#include "Components/CWeaponComponent.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Weapon/CWeapon.h"

FString UNS_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UNS_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCWeaponComponent* WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(WeaponComponent);

	ACPlayer* OwnerPlayer = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(OwnerPlayer);

	WeaponComponent->Weapon->AttackType = AttackType;
	WeaponComponent->Weapon->LaunchRate = LaunchRate;
	WeaponComponent->Weapon->Damage = OwnerPlayer->Cal_Damage(DamagePercent);

	WeaponComponent->Weapon->OnCollision();
}

void UNS_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCWeaponComponent* WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(WeaponComponent);

	WeaponComponent->Weapon->OffCollision();
}

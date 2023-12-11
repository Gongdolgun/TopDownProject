#include "Notifies/NS_Enemy_Collision.h"
#include "Components/CWeaponComponent_Enemy.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Weapon/CWeapon_Enemy.h"

FString UNS_Enemy_Collision::GetNotifyName_Implementation() const
{
	return "Enemy_Collision";
}

void UNS_Enemy_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	UCWeaponComponent_Enemy* WeaponComponent = CHelpers::GetComponent<UCWeaponComponent_Enemy>(MeshComp->GetOwner());
	CheckNull(WeaponComponent);

	ACEnemy* OwnerPlayer = Cast<ACEnemy>(MeshComp->GetOwner());
	CheckNull(OwnerPlayer);
	
	WeaponComponent->Weapon->Damage = OwnerPlayer->Cal_Damage(DamagePercent);

	WeaponComponent->Weapon->OnCollision();
}

void UNS_Enemy_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	UCWeaponComponent_Enemy* WeaponComponent = CHelpers::GetComponent<UCWeaponComponent_Enemy>(MeshComp->GetOwner());
	CheckNull(WeaponComponent);

	ACEnemy* OwnerPlayer = Cast<ACEnemy>(MeshComp->GetOwner());
	CheckNull(OwnerPlayer);

	WeaponComponent->Weapon->OffCollision();
}

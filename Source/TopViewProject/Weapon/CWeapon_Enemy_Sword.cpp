#include "Weapon/CWeapon_Enemy_Sword.h"
#include "Enemy/CEnemy.h"
#include "Global.h"

ACWeapon_Enemy_Sword::ACWeapon_Enemy_Sword()
{
	CHelpers::CreateComponent<UBoxComponent>(this, &Box_Collision, "Box_Collision", Mesh);
}

void ACWeapon_Enemy_Sword::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Mesh->AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "E_Sword_R");
}

void ACWeapon_Enemy_Sword::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

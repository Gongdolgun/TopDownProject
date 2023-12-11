#include "Weapon/CWeapon_Enemy_Lich.h"
#include "Enemy/CEnemy.h"
#include "Global.h"

ACWeapon_Enemy_Lich::ACWeapon_Enemy_Lich()
{
	CHelpers::CreateComponent<UBoxComponent>(this, &Box_Collision, "Box_Collision", Mesh);
}

void ACWeapon_Enemy_Lich::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Mesh->AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "MiddleFinger1_R");
}

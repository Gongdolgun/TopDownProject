#include "Weapon/CWeapon_Enemy.h"
#include "Global.h"
#include "Components/CAIBehaviorComponent.h"
#include "Components/ShapeComponent.h"
#include "Enemy/CEnemy.h"

ACWeapon_Enemy::ACWeapon_Enemy()
{
 	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", Root);
}

void ACWeapon_Enemy::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACEnemy>(GetOwner());
	Collisions = AActor::GetComponentsByClass(UShapeComponent::StaticClass());
	for (auto& Col : Collisions)
	{
		UShapeComponent* collision = Cast<UShapeComponent>(Col);
		collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		collision->OnComponentBeginOverlap.AddDynamic(this, &ACWeapon_Enemy::OnComponentBeginOverlap);
	}
}

void ACWeapon_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACWeapon_Enemy::DoAction()
{
	CheckNull(BaseAttack_Montage);

	FRotator Lookat = UKismetMathLibrary::FindLookAtRotation(Owner->GetActorLocation(), Owner->Behavior->GetTarget()->GetActorLocation());
	Owner->SetActorRotation(FRotator(0, Lookat.Yaw, 0));

	Owner->PlayAnimMontage(BaseAttack_Montage);
}

void ACWeapon_Enemy::OnCollision()
{
	for (auto& Col : Collisions)
	{
		UShapeComponent* collision = Cast<UShapeComponent>(Col);
		collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void ACWeapon_Enemy::OffCollision()
{
	for (auto& Col : Collisions)
	{
		UShapeComponent* collision = Cast<UShapeComponent>(Col);
		collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	HitActors.Empty();
}

void ACWeapon_Enemy::End_DoAction()
{
	Owner->Behavior->SetWaitMode();
}

void ACWeapon_Enemy::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != Owner)
	{
		if (HitActors.Find(OtherActor) == -1)
		{
			HitActors.AddUnique(OtherActor);
			for (auto& hitActor : HitActors)
			{
				IIDamage* HitActor = Cast<IIDamage>(hitActor);

				if (!!HitActor)
				{
					HitActor->BaseAttack(EAttackType::None, Owner, 1, Damage, FVector::ZeroVector);
				}
			}
		}
	}
}


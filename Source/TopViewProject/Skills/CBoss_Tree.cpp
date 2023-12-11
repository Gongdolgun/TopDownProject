#include "Skills/CBoss_Tree.h"
#include "Components/BoxComponent.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Interfaces/IDamage.h"

ACBoss_Tree::ACBoss_Tree()
{
 	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");

	CHelpers::CreateComponent<UBoxComponent>(this, &Collision, "Collision", Root);
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Tree, "Tree", Root);
}

void ACBoss_Tree::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACBoss_Tree::OnComponentBeginOverlap);
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACBoss_Tree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBoss_Tree::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckNull(OtherActor);

	if (OtherActor != GetOwner())
	{
		IIDamage* HitActor = Cast<IIDamage>(OtherActor);
		CheckNull(HitActor);

		ACEnemy* OwnerPlayer = Cast<ACEnemy>(GetOwner());
		CheckNull(OwnerPlayer);

		HitActor->BaseAttack(EAttackType::None, GetOwner(), 1, OwnerPlayer->Cal_Damage(OwnerPlayer->Cal_Damage(300)), FVector::ZeroVector);
	}
}

void ACBoss_Tree::Explosion()
{
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

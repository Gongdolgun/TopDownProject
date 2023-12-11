#include "Skills/BP_Lich_BaseAttack.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Enemy/CEnemy.h"
#include "Interfaces/IDamage.h"

ABP_Lich_BaseAttack::ABP_Lich_BaseAttack()
{
 	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<USphereComponent>(this, &Collision, "Collision", Root);
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Attack, "Attack", Root);

	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &ProjectileMovement, "ProjectileMovement");
}

void ABP_Lich_BaseAttack::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABP_Lich_BaseAttack::OnComponentBeginOverlap);
}

void ABP_Lich_BaseAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABP_Lich_BaseAttack::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckNull(OtherActor);

	if (OtherActor != GetOwner())
	{
		IIDamage* HitActor = Cast<IIDamage>(OtherActor);
		CheckNull(HitActor);

		ACPlayer* hitActor = Cast<ACPlayer>(HitActor);

		ACEnemy* OwnerPlayer = Cast<ACEnemy>(GetOwner());
		CheckNull(OwnerPlayer);

		if(!!hitActor)
		{
			HitActor->BaseAttack(EAttackType::None, GetOwner(), 1.f, OwnerPlayer->Cal_Damage(100), FVector::ZeroVector);

			Destroy();
		}
	}
}

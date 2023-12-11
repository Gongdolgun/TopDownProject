#include "Skills/CKnockDown.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Interfaces/IDamage.h"
#include "Player/CPlayer.h"

ACKnockDown::ACKnockDown()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");

	CHelpers::CreateComponent<UBoxComponent>(this, &Collision, "Collision", Root);

	Collision->SetBoxExtent(FVector (200.f, 200.f, 32.f));
}

void ACKnockDown::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACKnockDown::OnComponentBeginOverlap);

	if (SocketName != "")
	{
		SetActorLocation(FVector::ZeroVector);
		SetActorRotation(FRotator::ZeroRotator);
		AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform, SocketName);
	}

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, FTimerDelegate::CreateLambda([&]()
	{
		Destroy();
	}), 0.01f, false);
}

void ACKnockDown::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckNull(OtherActor);

	if(OtherActor != GetOwner())
	{
		IIDamage* HitActor = Cast<IIDamage>(OtherActor);
		CheckNull(HitActor);

		ACPlayer* OwnerPlayer = Cast<ACPlayer>(GetOwner());
		CheckNull(OwnerPlayer);

		HitActor->BaseAttack(AttackType, GetOwner(), PlayRate, OwnerPlayer->Cal_Damage(DamagePercent), LaunchRate);
	}
}

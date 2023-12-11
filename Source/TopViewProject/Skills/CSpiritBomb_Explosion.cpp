#include "Skills/CSpiritBomb_Explosion.h"
#include "Global.h"
#include "NiagaraFunctionLibrary.h"
#include "Interfaces/IDamage.h"
#include "Player/CPlayer.h"

ACSpiritBomb_Explosion::ACSpiritBomb_Explosion()
{
 	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");

	CHelpers::CreateComponent<USphereComponent>(this, &Collision, "Collision", Root);

	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Sphere1, "Sphere1", Root);
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Sphere2, "Sphere2", Root);
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Sphere3, "Sphere3", Root);
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Sphere4, "Sphere4", Root);

	CHelpers::CreateActorComponent<UTimelineComponent>(this, &Timeline, "Timeline");
	CHelpers::CreateActorComponent<URotatingMovementComponent>(this, &RotatingMovement, "RotatingMovement");

	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Collision->SetRelativeLocation(FVector(0, 0, 90));
	Collision->SetSphereRadius(140);
}

void ACSpiritBomb_Explosion::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACSpiritBomb_Explosion::OnComponentBeginOverlap);

	if (!!Curve)
	{
		FOnTimelineFloat timeline;
		FOnTimelineEvent timeline_End;
		timeline.BindUFunction(this, "Timeline_Func");
		timeline_End.BindUFunction(this, "Timeline_End");

		Timeline->AddInterpFloat(Curve, timeline);
		Timeline->SetTimelineFinishedFunc(timeline_End);
		Timeline->SetLooping(false);
		Timeline->SetPlayRate(0.3);
	}

	Timeline->PlayFromStart();
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CS_Base, 0.1f);
	CheckNull(Smoke);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Smoke, GetActorLocation());

	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, FTimerDelegate::CreateLambda([&]()
	{
		Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	}), 0.1f, false);

	FTimerHandle timer2;
	GetWorld()->GetTimerManager().SetTimer(timer2, FTimerDelegate::CreateLambda([&]()
	{
		Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}), 0.11f, false);
}

void ACSpiritBomb_Explosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACSpiritBomb_Explosion::Timeline_Func(float Output)
{
	Sphere1->SetWorldScale3D(FVector(UKismetMathLibrary::Lerp(1.6, Scale, Output), UKismetMathLibrary::Lerp(1.6, Scale, Output), UKismetMathLibrary::Lerp(1.6, Scale, Output)));
	Sphere2->SetWorldScale3D(FVector(UKismetMathLibrary::Lerp(1.6, Scale, Output), UKismetMathLibrary::Lerp(1.6, Scale, Output), UKismetMathLibrary::Lerp(1.6, Scale, Output)));
	Sphere3->SetWorldScale3D(FVector(UKismetMathLibrary::Lerp(1.6, Scale, Output), UKismetMathLibrary::Lerp(1.6, Scale, Output), UKismetMathLibrary::Lerp(1.6, Scale, Output)));
	Sphere4->SetWorldScale3D(FVector(UKismetMathLibrary::Lerp(1.6, Scale, Output), UKismetMathLibrary::Lerp(1.6, Scale, Output), UKismetMathLibrary::Lerp(1.6, Scale, Output)));

	if(!!CS_Base)
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CS_Base, CS_Scale);
}

void ACSpiritBomb_Explosion::Timeline_End()
{
	Destroy();
}

void ACSpiritBomb_Explosion::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckNull(OtherActor);

	if (OtherActor != GetOwner())
	{
		IIDamage* HitActor = Cast<IIDamage>(OtherActor);
		CheckNull(HitActor);

		ACPlayer* OwnerPlayer = Cast<ACPlayer>(GetOwner());
		CheckNull(OwnerPlayer);

		HitActor->BaseAttack(EAttackType::KnockDown, GetOwner(), 1, OwnerPlayer->Cal_Damage(3500), FVector::ZeroVector);
	}
}

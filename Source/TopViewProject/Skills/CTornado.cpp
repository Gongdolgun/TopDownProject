#include "Skills/CTornado.h"
#include "Global.h"
#include "Enemy/CEnemy.h"
#include "Interfaces/IDamage.h"

ACTornado::ACTornado()
{
 	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");

	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Tornado, "Tornado", Root);
	CHelpers::CreateComponent<UCapsuleComponent>(this, &Collision, "Collision", Tornado);

	Tornado->SetRelativeScale3D(FVector(0.6f, 0.6f, 0.6f));

	Collision->SetCapsuleHalfHeight(400.f);
	Collision->SetCapsuleRadius(200.f);
	Collision->SetRelativeLocation(FVector(0, 0, 215.f));
}

void ACTornado::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Destroy, FTimerDelegate::CreateLambda([&]()
	{
		Destroy();

	}),1.9f, false );

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACTornado::OnComponentBeginOverlap);
}

void ACTornado::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Hit);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Destroy);
}

void ACTornado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACTornado::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor != GetOwner())
	{
		ACEnemy* Enemy = Cast<ACEnemy>(OtherActor);
		IIDamage* HitActor = Cast<IIDamage>(Enemy);

		ACPlayer* OwnerPlayer = Cast<ACPlayer>(GetOwner());
		CheckNull(OwnerPlayer);

		if (!!HitActor)
			HitActors.AddUnique(HitActor);

		if(HitActors.Num() > 0)
		{

			for(auto& Hit : HitActors)
			{
				if (!!Hit)
					Hit->BaseAttack(EAttackType::KnockDown, GetOwner(), 1, OwnerPlayer->Cal_Damage(300.f), FVector(0, 0, LaunchScale));
			}

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_Hit, FTimerDelegate::CreateLambda([=]()
			{
				for (auto& Hit : HitActors)
				{
					if(!!Hit)
						Hit->BaseAttack(EAttackType::KnockDown, GetOwner(), 1, OwnerPlayer->Cal_Damage(300.f), FVector(0, 0, LaunchScale));
				}

				if(!!CameraShake)
					GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CameraShake, ShakeScale);

			}), 0.5f, true);
		}

	}
		
}

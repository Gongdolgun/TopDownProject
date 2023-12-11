#include "Skills/CSpritBomb.h"
#include "Skills/CSpiritBomb_Explosion.h"
#include "Global.h"
#include "NiagaraFunctionLibrary.h"

ACSpritBomb::ACSpritBomb()
{
 	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");

	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Sphere1, "Sphere1", Root);
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Sphere2, "Sphere2", Root);
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Sphere3, "Sphere3", Root);
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Sphere4, "Sphere4", Root);

	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Line1, "Line1", Root);
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Line2, "Line2", Root);

	CHelpers::CreateComponent<USphereComponent>(this, &Collision, "Collision", Root);

	CHelpers::CreateActorComponent<UTimelineComponent>(this, &Timeline, "Timeline");

	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &ProjectileMovement, "ProjectileMovement");

	Line1->SetRelativeLocation(FVector(0, 0, 90));
	Line2->SetRelativeLocation(FVector(0, 0, 90));

	Collision->SetRelativeLocation(FVector(0, 0, 90));
	Collision->SetSphereRadius(30.f);

	ProjectileMovement->SetAutoActivate(false);
	ProjectileMovement->InitialSpeed = 500.f;
}

void ACSpritBomb::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACSpritBomb::OnComponentBeginOverlap);

	if(!!Curve)
	{
		FOnTimelineFloat timeline;
		FOnTimelineEvent timeline_End;
		timeline.BindUFunction(this, "Timeline_Func");
		timeline_End.BindUFunction(this, "Timeline_End");

		Timeline->AddInterpFloat(Curve, timeline);
		Timeline->SetTimelineFinishedFunc(timeline_End);
		Timeline->SetLooping(false);
		Timeline->SetPlayRate(0.2);
	}

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
	TEnumAsByte<EObjectTypeQuery> WorldDynamic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic);
	ObjectTypes.Add(WorldStatic);
	ObjectTypes.Add(WorldDynamic);

	TArray<AActor*> ignores;
	ignores.Add(GetOwner());

	FHitResult hitResult;
	UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), GetActorLocation(), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().X - 1000.f), ObjectTypes, false, ignores, EDrawDebugTrace::None, hitResult, true);

	if (!!hitResult.bBlockingHit)
	{
		CheckNull(Ground_Effect);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Ground_Effect, hitResult.Location);
	}

	Timeline->PlayFromStart();
}

void ACSpritBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void ACSpritBomb::Timeline_Func(float Output)
{
	Sphere1->SetWorldScale3D(FVector(UKismetMathLibrary::Lerp(0, Scale, Output), UKismetMathLibrary::Lerp(0, Scale, Output), UKismetMathLibrary::Lerp(0, Scale, Output)));
	Sphere2->SetWorldScale3D(FVector(UKismetMathLibrary::Lerp(0, Scale, Output), UKismetMathLibrary::Lerp(0, Scale, Output), UKismetMathLibrary::Lerp(0, Scale, Output)));
	Sphere3->SetWorldScale3D(FVector(UKismetMathLibrary::Lerp(0, Scale, Output), UKismetMathLibrary::Lerp(0, Scale, Output), UKismetMathLibrary::Lerp(0, Scale, Output)));
	Sphere4->SetWorldScale3D(FVector(UKismetMathLibrary::Lerp(0, Scale, Output), UKismetMathLibrary::Lerp(0, Scale, Output), UKismetMathLibrary::Lerp(0, Scale, Output)));

	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CS_Base, CS_Scale);
}

void ACSpritBomb::Timeline_End()
{
	ProjectileMovement->SetActive(true);
}

void ACSpritBomb::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FActorSpawnParameters param;
	param.Owner = GetOwner();
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (OtherActor != GetOwner())
	{
		GetWorld()->SpawnActor<ACSpiritBomb_Explosion>(BP_SpiritBomb_Explosion, GetActorLocation(), FRotator::ZeroRotator, param);
		Destroy();
	}
}

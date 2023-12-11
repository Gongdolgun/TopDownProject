#include "Skills/CBlastFormation.h"
#include "Global.h"
#include "Enemy/CEnemy.h"

ACBlastFormation::ACBlastFormation()
{
 	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");

	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Layer0, "Layer0", Root);
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Layer1_1, "Layer1_1", Root);
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Layer1_2, "Layer1_2", Root);
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Layer1_3, "Layer1_3", Root);
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Layer2_1, "Layer2_1", Root);
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Layer2_2, "Layer2_2", Root);
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Layer2_3, "Layer2_3", Root);
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Layer2_4, "Layer2_4", Root);
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Layer2_5, "Layer2_5", Root);

	CHelpers::CreateComponent<UBoxComponent>(this, &Box_Layer0, "Box_Layer0", Root);
	CHelpers::CreateComponent<UBoxComponent>(this, &Box_Layer1, "Box_Layer1", Root);
	CHelpers::CreateComponent<UBoxComponent>(this, &Box_Layer2, "Box_Layer2", Root);

	Layer1_1->SetRelativeLocation(FVector(200, 0, 0));
	Layer1_2->SetRelativeLocation(FVector(200, -200, 0));
	Layer1_3->SetRelativeLocation(FVector(200, 200, 0));

	Layer2_1->SetRelativeLocation(FVector(400, -400, 0));
	Layer2_2->SetRelativeLocation(FVector(400, -200, 0));
	Layer2_3->SetRelativeLocation(FVector(400, 0, 0));
	Layer2_4->SetRelativeLocation(FVector(400, 200, 0));
	Layer2_5->SetRelativeLocation(FVector(400, 400, 0));

	Layer1_1->SetAutoActivate(false);
	Layer1_2->SetAutoActivate(false);
	Layer1_3->SetAutoActivate(false);
	Layer2_1->SetAutoActivate(false);
	Layer2_2->SetAutoActivate(false);
	Layer2_3->SetAutoActivate(false);
	Layer2_4->SetAutoActivate(false);
	Layer2_5->SetAutoActivate(false);

	Box_Layer1->SetRelativeLocation(FVector(200, 0, 0));
	Box_Layer2->SetRelativeLocation(FVector(400, 0, 0));

	Box_Layer0->SetBoxExtent(FVector(90, 70, 12));
	Box_Layer1->SetBoxExtent(FVector(90, 400, 12));
	Box_Layer2->SetBoxExtent(FVector(90, 600, 12));

	Box_Layer1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Box_Layer2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACBlastFormation::BeginPlay()
{
	Super::BeginPlay();

	Collisions = AActor::GetComponentsByClass(UShapeComponent::StaticClass());


	for(auto& Col : Collisions)
	{
		UShapeComponent* collision = Cast<UShapeComponent>(Col);
		collision->OnComponentBeginOverlap.AddDynamic(this, &ACBlastFormation::OnComponentBeginOverlap);
	}

	FTimerHandle timerHandle;

	GetWorld()->GetTimerManager().SetTimer(timerHandle, FTimerDelegate::CreateLambda([&]()
	{
		Layer1_1->Activate();
		Layer1_2->Activate();
		Layer1_3->Activate();

		Box_Layer0->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Box_Layer1->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		GetWorld()->GetTimerManager().ClearTimer(timerHandle);
	}), 0.5f, false);

	FTimerHandle timerHandle2;

	GetWorld()->GetTimerManager().SetTimer(timerHandle2, FTimerDelegate::CreateLambda([&]()
	{
		Layer2_1->Activate();
		Layer2_2->Activate();
		Layer2_3->Activate();
		Layer2_4->Activate();
		Layer2_5->Activate();

		Box_Layer1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Box_Layer2->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		GetWorld()->GetTimerManager().ClearTimer(timerHandle2);
	}), 1.4f, false);

	FTimerHandle timerHandle_Destroy;

	GetWorld()->GetTimerManager().SetTimer(timerHandle_Destroy, FTimerDelegate::CreateLambda([&]()
	{
		Destroy();
		
	}), 2.4f, false);
}

void ACBlastFormation::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACBlastFormation::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IIDamage* HitActor = Cast<IIDamage>(OtherActor);

	if(!!HitActor && OtherActor!= GetOwner())
	{
		ACPlayer* OwnerPlayer = Cast<ACPlayer>(GetOwner());
		CheckNull(OwnerPlayer);

		HitActor->BaseAttack(EAttackType::KnockDown, GetOwner(), 1, OwnerPlayer->Cal_Damage(DamagePercent), FVector(-1500, -1500, 0));
	}
}
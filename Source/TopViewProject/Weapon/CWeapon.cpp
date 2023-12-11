#include "Weapon/CWeapon.h"
#include "Animation/AnimMontage.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "Components/CMovementComponent.h"
#include "Components/ShapeComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/CPlayer.h"

ACWeapon::ACWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", Root);
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh2, "Mesh2", Root);
}

void ACWeapon::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACPlayer>(GetOwner());
	Collisions = AActor::GetComponentsByClass(UShapeComponent::StaticClass());
	for (auto& Col : Collisions)
	{
		UShapeComponent* collision = Cast<UShapeComponent>(Col);
		collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		collision->OnComponentBeginOverlap.AddDynamic(this, &ACWeapon::OnComponentBeginOverlap);
	}
}

void ACWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/*if(!!HitActors[0])
	{
		Owner->GetCurrentMontage()->RootMotionRootLock = ERootMotionRootLock::Zero;
	}*/
}

void ACWeapon::DoAction()
{
	UCMovementComponent* MovementComponent = CHelpers::GetComponent<UCMovementComponent>(Owner);
	CheckNull(MovementComponent);

	Owner->Stop();
	MovementComponent->DisableMove();

	if(!comboEnable)
	{
		if(BaseAttack[MontageNum])
		{
			if(Owner->StateComponent->IsIdleMode())
			{
				Owner->ChangeRotationToCursor();
				Owner->PlayAnimMontage(BaseAttack[MontageNum]);
				Owner->StateComponent->SetActionMode();
			}
		}
	}
	else
	{
		comboEnable = false;
		combo = true;
	}

}

void ACWeapon::Begin_DoAction()
{
	if(combo)
	{
		combo = false;
		MontageNum++;

		Owner->Timeline4->PlayFromStart();
		Owner->PlayAnimMontage(BaseAttack[MontageNum]);
	}
}

void ACWeapon::End_DoAction()
{
	Owner->StateComponent->SetIdleMode();
	Owner->MovementComponent->EnableMove();

	Owner->GetCharacterMovement()->MaxWalkSpeed = 600.f;
	Owner->GetCharacterMovement()->MaxAcceleration = 2048.f;
	MontageNum = 0;
}

void ACWeapon::OnCollision()
{
	for(auto& Col : Collisions)
	{
		UShapeComponent* collision = Cast<UShapeComponent>(Col);
		collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void ACWeapon::OffCollision()
{
	for (auto& Col : Collisions)
	{
		UShapeComponent* collision = Cast<UShapeComponent>(Col);
		collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	HitActors.Empty();
}

void ACWeapon::CameraShake(TSubclassOf<UMatineeCameraShake> InCameraShake, float InScale)
{
	CheckNull(InCameraShake);
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(InCameraShake, InScale);
}

void ACWeapon::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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
					HitActor->BaseAttack(AttackType, Owner, 1, Damage, LaunchRate);
					CameraShake(CS_Base, CS_Scale[MontageNum]);
				}
			}
		}
	}
}

void ACWeapon::Skill_TakeDown()
{
}

void ACWeapon::Skill_BlastFormation()
{
}

void ACWeapon::Skill_ContinuousPush()
{
}

void ACWeapon::Skill_Fury()
{
}

void ACWeapon::Skill_Tornado()
{
}

void ACWeapon::Skill_OnePunch()
{
}

void ACWeapon::Skill_SpiritBomb()
{
}

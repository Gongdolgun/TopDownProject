#include "Weapon/CWeapon_Fist.h"
#include "Components/SphereComponent.h"
#include "Components/CMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Global.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/CStateComponent.h"
#include "Player/CPlayer.h"
#include "Skills/CBlastFormation.h"
#include "Skills/CSpritBomb.h"
#include "GameInstance_Test.h"

ACWeapon_Fist::ACWeapon_Fist()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set Mesh
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Sphere_2.Sphere_2'");
	Mesh->SetStaticMesh(mesh);
	Mesh2->SetStaticMesh(mesh);

	Mesh->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
	Mesh2->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));

	// Set SphereCollision
	CHelpers::CreateComponent<USphereComponent>(this, &Sphere_R, "Sphere_R", Mesh);
	CHelpers::CreateComponent<USphereComponent>(this, &Sphere_L, "Sphere_L", Mesh2);
	CHelpers::CreateComponent<USphereComponent>(this, &Sphere_Leg_R, "Sphere_Leg_R", Root);
	CHelpers::CreateComponent<USphereComponent>(this, &Sphere_Leg_L, "Sphere_Leg_L", Root);

}

void ACWeapon_Fist::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh2->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Mesh->AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "hand_r");
	Mesh2->AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "hand_l");
	Sphere_Leg_L->AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "foot_l");
	Sphere_Leg_R->AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "foot_r");
	GameInstance = Cast<UGameInstance_Test>(GetGameInstance());
}

void ACWeapon_Fist::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(!!GameInstance)
	{
		if (!UKismetMathLibrary::NearlyEqual_FloatFloat(GameInstance->QSkill_Cooltime, 0, 0.1))
			GameInstance->QSkill_Cooltime -= 0.01f;

		if (!UKismetMathLibrary::NearlyEqual_FloatFloat(GameInstance->WSkill_Cooltime, 0, 0.1))
			GameInstance->WSkill_Cooltime -= 0.01f;

		if (!UKismetMathLibrary::NearlyEqual_FloatFloat(GameInstance->ESkill_Cooltime, 0, 0.1))
			GameInstance->ESkill_Cooltime -= 0.01f;

		if (!UKismetMathLibrary::NearlyEqual_FloatFloat(GameInstance->ASkill_Cooltime, 0, 0.1))
			GameInstance->ASkill_Cooltime -= 0.01f;

		if (!UKismetMathLibrary::NearlyEqual_FloatFloat(GameInstance->SSkill_Cooltime, 0, 0.1))
			GameInstance->SSkill_Cooltime -= 0.01f;

		if (!UKismetMathLibrary::NearlyEqual_FloatFloat(GameInstance->DSkill_Cooltime, 0, 0.1))
			GameInstance->DSkill_Cooltime -= 0.01f;

		if (!UKismetMathLibrary::NearlyEqual_FloatFloat(GameInstance->VSkill_Cooltime, 0, 0.1))
			GameInstance->VSkill_Cooltime -= 0.01f;
	}
}

void ACWeapon_Fist::Skill_TakeDown()
{
	Super::Skill_TakeDown();

	Owner->MovementComponent->DisableMove();

	if(!!TakeDown_Montage && !Owner->StateComponent->IsSkillMode())
	{
		GameInstance->QSkill_Cooltime = GameInstance->QSkill_MaxCooltime;
		Owner->MovementComponent->DisableSprint();			// 내려찍기 전까지는 대쉬 못씀
		Owner->StateComponent->SetSkillMode();				// 스킬 사용중에는 캔슬 불가 (기본공격, Idle모드일땐 가능)
		Owner->ChangeRotationToCursor();					// 커서방향으로 캐릭터 틀어주기
		Owner->PlayAnimMontage(TakeDown_Montage);
		Owner->SetMP(380);

		FVector Location = Owner->GetActorLocation() + (Owner->GetActorForwardVector() * 1000.f);

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
		TEnumAsByte<EObjectTypeQuery> Pawn = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
		ObjectTypes.Add(WorldStatic);
		ObjectTypes.Add(Pawn);

		TArray<AActor*> ignores;
		ignores.Add(Owner);

		FHitResult hitResult;
		UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Owner->GetActorLocation(), Location, ObjectTypes, false, ignores, EDrawDebugTrace::None, hitResult, true);

		Owner->Stop();
		Owner->GetCharacterMovement()->MaxWalkSpeed = 1200.f;
		Owner->GetCharacterMovement()->MaxAcceleration = 20000.f;
		

		if (!hitResult.GetActor())
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(Owner->GetController(), Location);
		}

		else
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(Owner->GetController(), hitResult.Location);
		}
	}
}

void ACWeapon_Fist::Skill_BlastFormation()
{
	Super::Skill_BlastFormation();

	CheckNull(blastFormation);

	if (!!BlastFormation_Montage && !Owner->StateComponent->IsSkillMode())
	{
		GameInstance->WSkill_Cooltime = GameInstance->WSkill_MaxCooltime;
		Owner->MovementComponent->DisableMove();
		Owner->MovementComponent->DisableSprint();
		Owner->StateComponent->SetSkillMode();
		Owner->ChangeRotationToCursor();
		Owner->Stop();
		Owner->PlayAnimMontage(BlastFormation_Montage);
		Owner->SetMP(420);

		FActorSpawnParameters param;
		param.Owner = Owner;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector Location = (Owner->GetActorLocation() + (Owner->GetActorForwardVector() * 200.f));
		float location_Z = Location.Z - Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

		Owner->GetWorld()->SpawnActor<ACBlastFormation>(blastFormation, FVector(Location.X, Location.Y, location_Z), UKismetMathLibrary::MakeRotFromX(Owner->GetActorForwardVector()), param);

	}
}

void ACWeapon_Fist::Skill_ContinuousPush()
{
	Super::Skill_ContinuousPush();

	if (!!ContinuosPush_Montage && !Owner->StateComponent->IsSkillMode())
	{
		GameInstance->ESkill_Cooltime = GameInstance->ESkill_MaxCooltime;

		Owner->MovementComponent->EnableMove();
		Owner->StateComponent->SetSkillMode();
		Owner->ChangeRotationToCursor();
		Owner->Stop();
		Owner->PlayAnimMontage(ContinuosPush_Montage);
		Owner->SetMP(250);

		FVector Location = Owner->GetActorLocation() + (Owner->GetActorForwardVector() * 1000.f);

		Owner->GetCharacterMovement()->MaxWalkSpeed = 300.f;
		Owner->GetCharacterMovement()->MaxAcceleration = 20000.f;

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Owner->GetController(), Location);
		
	}
}

void ACWeapon_Fist::Skill_Fury()
{
	Super::Skill_Fury();

	if(!!Fury_Montage)
	{
		GameInstance->DSkill_Cooltime = GameInstance->DSkill_MaxCooltime;
		Owner->MovementComponent->DisableMove();
		Owner->StateComponent->SetSkillMode();
		Owner->ChangeRotationToCursor();
		Owner->Stop();
		Owner->SetMP(600);

		Owner->PlayAnimMontage(Fury_Montage, 1.5f);
	}
}

void ACWeapon_Fist::Skill_Tornado()
{
	Super::Skill_Tornado();

	if(!!Tornado_Montage && !Owner->StateComponent->IsSkillMode())
	{
		GameInstance->ASkill_Cooltime = GameInstance->ASkill_MaxCooltime;

		Owner->MovementComponent->DisableMove();
		Owner->StateComponent->SetSkillMode();
		Owner->ChangeRotationToCursor();
		Owner->Stop();
		Owner->SetMP(450);

		Owner->PlayAnimMontage(Tornado_Montage);
	}
}

void ACWeapon_Fist::Skill_OnePunch()
{
	Super::Skill_OnePunch();

	if (!!OnePunch_Montage && !Owner->StateComponent->IsSkillMode())
	{
		GameInstance->SSkill_Cooltime = GameInstance->SSkill_MaxCooltime;

		Owner->MovementComponent->DisableMove();
		Owner->StateComponent->SetSkillMode();
		Owner->ChangeRotationToCursor();
		Owner->Stop();
		Owner->SetMP(300);

		Owner->PlayAnimMontage(OnePunch_Montage);
	}
}

void ACWeapon_Fist::Skill_SpiritBomb()
{
	Super::Skill_SpiritBomb();

	CheckNull(Launch_Montage);
	CheckNull(SpiritBomb_Start_Montage);
	CheckNull(SpiritBomb_End_Montage);
	CheckNull(BP_SpiritBomb);

	if (!Owner->StateComponent->IsSkillMode())
	{
		GameInstance->VSkill_Cooltime = GameInstance->VSkill_MaxCooltime;

		Owner->MovementComponent->DisableMove();
		Owner->MovementComponent->DisableSprint();
		Owner->StateComponent->SetSkillMode();
		Owner->ChangeRotationToCursor();
		Owner->Stop();

		Owner->PlayAnimMontage(Launch_Montage);

		FTimerHandle t_step1;

		GetWorld()->GetTimerManager().SetTimer(t_step1, FTimerDelegate::CreateLambda([&]()
		{
			Owner->LaunchCharacter(FVector(0, 0, 900), false, false);

			GetWorld()->GetTimerManager().ClearTimer(t_step1);

			FTimerHandle t_step2;

			GetWorld()->GetTimerManager().SetTimer(t_step1, FTimerDelegate::CreateLambda([&]()
			{
				Owner->PlayAnimMontage(SpiritBomb_Start_Montage);
				Owner->GetCharacterMovement()->Velocity = FVector::ZeroVector;
				Owner->GetCharacterMovement()->GravityScale = 0.0f;

				FActorSpawnParameters param;
				param.Owner = Owner;
				param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				FVector location = FVector(Owner->GetActorLocation().X, Owner->GetActorLocation().Y, Owner->GetActorLocation().Z + 180);
				FRotator rotation = UKismetMathLibrary::MakeRotFromX(Owner->GetActorForwardVector());

				GetWorld()->SpawnActor<ACSpritBomb>(BP_SpiritBomb, location, rotation, param);

				GetWorld()->GetTimerManager().ClearTimer(t_step2);

				FTimerHandle t_step3;

				GetWorld()->GetTimerManager().SetTimer(t_step1, FTimerDelegate::CreateLambda([&]()
				{
					Owner->PlayAnimMontage(SpiritBomb_End_Montage);

					GetWorld()->GetTimerManager().ClearTimer(t_step3);

					FTimerHandle t_step4;

					GetWorld()->GetTimerManager().SetTimer(t_step1, FTimerDelegate::CreateLambda([&]()
					{
						Owner->GetCharacterMovement()->GravityScale = 1.f;

						GetWorld()->GetTimerManager().ClearTimer(t_step4);
					}), 0.6f, false);
				}), 4.7f, false);
			}), 0.5f, false);
		}), 0.2f, false);
	}
}

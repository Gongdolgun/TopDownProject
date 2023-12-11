#include "CPlayer.h"

#include "GameInstance_Test.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Global.h"
#include "ParameterCollection.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CMovementComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CWeaponComponent.h"
#include "Components/TimelineComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Engine/World.h"
#include "Widgets/CUserWidget_Damage.h"
#include "Components/WidgetComponent.h"

ACPlayer::ACPlayer()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Set Datas
	CHelpers::GetAsset<UNiagaraSystem>(&SprintParticle, "NiagaraSystem'/Game/BlinkAndDashVFX/VFX/Niagara/System/Flight/NS_Flight_Hover_Start.NS_Flight_Hover_Start'");
	CHelpers::GetAsset<UNiagaraSystem>(&SprintParticle2, "NiagaraSystem'/Game/BlinkAndDashVFX/VFX/Niagara/System/Flight/NS_Flight_HighSpeed_Start1.NS_Flight_HighSpeed_Start1'");

	// Set Component
	CHelpers::CreateActorComponent<UCWeaponComponent>(this, &WeaponComponent, "WeaponComponent");
	CHelpers::CreateActorComponent<UCStateComponent>(this, &StateComponent, "StateComponent");
	CHelpers::CreateActorComponent<UCMovementComponent>(this, &MovementComponent, "MovementComponent");
	CHelpers::CreateComponent<UWidgetComponent>(this, &WDG_Damage, "Damage", GetCapsuleComponent());

	// Set AfterEffect
	CHelpers::CreateComponent<UNiagaraComponent>(this, &AfterEffect, "AfterEffect", GetCapsuleComponent());
	AfterEffect->SetAutoActivate(false);

	// Set SkeletalMesh
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -105));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// Set Timeline
	CHelpers::CreateActorComponent<UTimelineComponent>(this, &Timeline, "Timeline");
	CHelpers::CreateActorComponent<UTimelineComponent>(this, &Timeline2, "Timeline2");
	CHelpers::CreateActorComponent<UTimelineComponent>(this, &Timeline3, "Timeline3");
	CHelpers::CreateActorComponent<UTimelineComponent>(this, &Timeline4, "Timeline4");
	
	// Set Animation
	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/Player/ABP_Player.ABP_Player_C'");
	CHelpers::GetAsset<UAnimMontage>(&SprintMotion, "AnimMontage'/Game/Anim/Montages/06_Frank_Moves_Dash_Inplace_Montage.06_Frank_Moves_Dash_Inplace_Montage'");
	GetMesh()->SetAnimInstanceClass(animInstance);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	SpringArm->TargetArmLength = TargetArmLength;
	SpringArm->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));
	SpringArm->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 20.0f;


	// Create a camera...
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Damage
	maxDamage = 500000;
	minDamage = maxDamage * 0.7f;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	if(CurveFloat)
	{
		FOnTimelineFloat timeline;
		timeline.BindUFunction(this, "BeginSprint");

		FOnTimelineFloat timeline_Rot;
		timeline_Rot.BindUFunction(this, "ChangeRotationToCursor");

		// Spint Timeline
		Timeline->AddInterpFloat(CurveFloat, timeline);
		Timeline->SetLooping(false);
		Timeline->SetPlayRate(10);

		Timeline4->AddInterpFloat(CurveFloat, timeline_Rot);
		Timeline4->SetLooping(false);
		Timeline4->SetPlayRate(5);
	}

	if(ZoomCurve)		// Zoom Timeline
	{
		FOnTimelineFloat timeline_ZoomIn;
		timeline_ZoomIn.BindUFunction(this, "BeginZoomIn");
		
		FOnTimelineFloat timeline_ZoomOut;
		timeline_ZoomOut.BindUFunction(this, "BeginZoomOut");

		Timeline2->AddInterpFloat(ZoomCurve, timeline_ZoomIn);
		Timeline2->SetLooping(false);
		Timeline2->SetPlayRate(1.5);

		Timeline3->AddInterpFloat(ZoomCurve, timeline_ZoomOut);
		Timeline3->SetLooping(false);
		Timeline3->SetPlayRate(1.5);
	}

	CameraHeight = Camera->GetComponentLocation().Z;

	gameInstance = Cast<UGameInstance_Test>(GetGameInstance());
}

void ACPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = Camera->GetComponentLocation();
				FVector EndLocation = Camera->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_GameTraceChannel3, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_GameTraceChannel3, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
	// 카메라 Z축 고정
	/*if(!bZooming)
		Camera->SetWorldLocation(FVector( Camera->GetComponentLocation().X, Camera->GetComponentLocation().Y, CameraHeight));*/

	if (!UKismetMathLibrary::NearlyEqual_FloatFloat(gameInstance->Player_MP, gameInstance->Player_MaxMP, 0.1f))
	{
		gameInstance->Player_MP += 2.f;
	}
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACPlayer::OnSprint);
	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &ACPlayer::OnZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &ACPlayer::OnZoomOut);
	PlayerInputComponent->BindAction("Action", IE_Pressed, WeaponComponent, &UCWeaponComponent::DoAction);

	PlayerInputComponent->BindAction("QSkill", IE_Pressed, WeaponComponent, &UCWeaponComponent::Q_Skill);
	PlayerInputComponent->BindAction("WSkill", IE_Pressed, WeaponComponent, &UCWeaponComponent::W_Skill);
	PlayerInputComponent->BindAction("ESkill", IE_Pressed, WeaponComponent, &UCWeaponComponent::E_Skill);
	PlayerInputComponent->BindAction("DSkill", IE_Pressed, WeaponComponent, &UCWeaponComponent::R_Skill);
	PlayerInputComponent->BindAction("ASkill", IE_Pressed, WeaponComponent, &UCWeaponComponent::A_Skill);
	PlayerInputComponent->BindAction("SSkill", IE_Pressed, WeaponComponent, &UCWeaponComponent::S_Skill);

	PlayerInputComponent->BindAction("VSkill", IE_Pressed, WeaponComponent, &UCWeaponComponent::V_Skill);
}

void ACPlayer::BaseAttack(EAttackType InAttackType, AActor* Attacker, float PlayRate, float Damage, FVector LaunchRate)
{
	IIDamage::BaseAttack(InAttackType, Attacker, PlayRate, Damage, LaunchRate);

	LaunchCharacter(FVector(GetActorForwardVector().X * LaunchRate.X, GetActorForwardVector().Y * LaunchRate.Y, LaunchRate.Z), false, false);

	switch (InAttackType)
	{
		case EAttackType::Stagger:
			if(!!StaggerMontage)
			{
				PlayAnimMontage(StaggerMontage, PlayRate);
				break;
			}

		case EAttackType::KnockDown:
			if(!!KnockDownMontage)
			{
				PlayAnimMontage(KnockDownMontage, PlayRate);
				break;
			}
	}

	// Set Damage
	{
		if (!!gameInstance)
			gameInstance->Player_HP = UKismetMathLibrary::Clamp(gameInstance->Player_HP - Damage, 0, gameInstance->Player_MaxHP);
	}


	// Damage UI
	{
		CheckNull(WDG_Damage->GetWidget());

		UCUserWidget_Damage* userwidget_Damage;
		userwidget_Damage = Cast<UCUserWidget_Damage>(WDG_Damage->GetWidget());

		FString damage;
		damage = FString::FormatAsNumber(Damage);

		userwidget_Damage->PlayerDamage(damage);
	}
}

void ACPlayer::OnSprint()
{
	if(MovementComponent->IsEnableSprint())
	{
		StopAnimMontage(GetCurrentMontage());

		ActorLocation = GetActorLocation();
		ChangeRotationToCursor();				// 커서 방향으로 캐릭터 회전
		
		Stop();									// 커서로 이동 못하게 스탑
		MovementComponent->DisableMove();		// 스프린트 도중 이동 불가

		PlayAnimMontage(SprintMotion);

		if(!!SprintParticle && !!SprintParticle2)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SprintParticle, GetActorLocation() + (GetActorForwardVector() * SprintDistance));
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SprintParticle2, GetActorLocation() + (GetActorForwardVector() * SprintDistance / 2));
		}

		FVector Destination = GetActorLocation() + GetActorForwardVector() * SprintDistance;

		GetCharacterMovement()->MaxAcceleration = 60000.f;
		GetCharacterMovement()->MaxWalkSpeed = 10000.f;

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
		TEnumAsByte<EObjectTypeQuery> Pawn = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
		ObjectTypes.Add(WorldStatic);
		ObjectTypes.Add(Pawn);

		TArray<AActor*> ignores;
		ignores.Add(this);

		FHitResult hitResult;
		UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), GetActorLocation(), Destination, ObjectTypes, false, ignores, EDrawDebugTrace::None, hitResult, true);

		if(!hitResult.GetActor())
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), Destination);
		}

		else
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), hitResult.Location);
		}

		// Timeline->PlayFromStart();
	}
}

void ACPlayer::OnZoomIn()
{
	if(!bZooming && SpringArm->TargetArmLength != 300)
	{
		bZooming = true;
		Timeline2->PlayFromStart();
	}
}

void ACPlayer::OnZoomOut()
{
	if (!bZooming && SpringArm->TargetArmLength != TargetArmLength)
	{
		bZooming = true;
		Timeline3->PlayFromStart();
	}
}

void ACPlayer::Stop()
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), GetActorLocation());
}

void ACPlayer::ChangeRotationToCursor()
{
	FRotator Lookat = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CursorToWorld->GetComponentLocation());
	SetActorRotation(FRotator(GetActorRotation().Pitch, Lookat.Yaw, GetActorRotation().Roll));
}

float ACPlayer::Cal_Damage(float percent)
{
	FinalDamage = UKismetMathLibrary::RandomFloatInRange(minDamage, maxDamage);

	int Critical_tmp;
	Critical_tmp = UKismetMathLibrary::RandomInteger64InRange(1, 100);

	Critical_tmp <= CriticalRate ? 	bCritical = true : bCritical = false;

	if(bCritical == true)
	{
		return FinalDamage * (percent * 0.01f) * 1.5f;
	}

	return FinalDamage * (percent * 0.01f);
}

void ACPlayer::SetMP(float MPRate)
{
	if(!!gameInstance)
		gameInstance->Player_MP = UKismetMathLibrary::Clamp(gameInstance->Player_MP - MPRate, 0, gameInstance->Player_MaxMP);
}

void ACPlayer::ChangeRotationToCursor(float Output)
{
	FRotator Lookat = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CursorToWorld->GetComponentLocation());
	SetActorRotation(FRotator(GetActorRotation().Pitch, UKismetMathLibrary::Lerp(GetActorRotation().Yaw ,Lookat.Yaw, Output), GetActorRotation().Roll));
}

void ACPlayer::BeginSprint(float Output)
{
	FVector forwardVec = GetActorForwardVector();
	FVector Destination = ActorLocation + (forwardVec * SprintDistance);

	SetActorLocation(FMath::Lerp(ActorLocation, Destination, Output));
}

void ACPlayer::BeginZoomIn(float Output)
{
	//CameraHeight = Camera->GetComponentLocation().Z;
	SpringArm->TargetArmLength = FMath::Lerp(TargetArmLength, 300.f, Output);
	SpringArm->SetRelativeRotation(FRotator(FMath::Lerp(-50, 0, Output), 0.f, 0.f));

	if(Output == 1)
		bZooming = false;
}

void ACPlayer::BeginZoomOut(float Output)
{
	//CameraHeight = Camera->GetComponentLocation().Z;
	SpringArm->TargetArmLength = FMath::Lerp(300.f, TargetArmLength, Output);
	SpringArm->SetRelativeRotation(FRotator(FMath::Lerp(0, -50, Output), 0.f, 0.f));

	if (Output == 1)
		bZooming = false;
}

void ACPlayer::DoAction()
{
	WeaponComponent->DoAction();
}
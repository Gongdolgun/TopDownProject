#include "CPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "CPlayer.h"
#include "Global.h"
#include "Components/CMovementComponent.h"
#include "Engine/World.h"

ACPlayerController::ACPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ACPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ACPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ACPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ACPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ACPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ACPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &ACPlayerController::OnResetVR);
}

void ACPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ACPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ACPlayer* MyPawn = Cast<ACPlayer>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_GameTraceChannel3, false, Hit);

		if (Hit.bBlockingHit)
		{
			Destination = Hit.ImpactPoint;
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void ACPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ACPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	UCMovementComponent* MovementComponent = CHelpers::GetComponent<UCMovementComponent>(MyPawn);
	CheckNull(MovementComponent);

	if(MovementComponent->IsEnableMove())
	{
		if (MyPawn)
		{
			float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

			if ((Distance > 120.0f))
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ACPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;

	if (ACPlayer* MyPawn = Cast<ACPlayer>(GetPawn()))
	{
		FVector Location = FVector(MyPawn->CursorToWorld->GetComponentLocation().X, MyPawn->CursorToWorld->GetComponentLocation().Y, MyPawn->CursorToWorld->GetComponentLocation().Z + 20.f);
		FQuat Rotation = FQuat(MyPawn->CursorToWorld->GetComponentRotation());
		CHelpers::PlayEffect(GetWorld(), MyPawn->ClickParticle, FTransform(Location));
	}
}

void ACPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
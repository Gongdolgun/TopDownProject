#include "Components/CFeetComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

// #define LOG_UCFeetComponent

UCFeetComponent::UCFeetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCFeetComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UCFeetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float leftDistance, rightDistance;
	FRotator leftRotation, rightRotation;

	// LineTrace를 통해 위치와 회전각 계산
	Trace(LeftSocket, leftDistance, leftRotation);
	Trace(RightSocket, rightDistance, rightRotation);

	// 왼쪽 발과 오른쪽 발이 지면에서 얼마나 떨어져 있는지를 측정하고 그 중에서 더 작은 값을 선택
	float offset = FMath::Min(leftDistance, rightDistance);
	Data.PelvisDistance.Z = UKismetMathLibrary::FInterpTo(Data.PelvisDistance.Z, offset, DeltaTime, InterpSpeed);

	Data.LeftDistance.X = UKismetMathLibrary::FInterpTo(Data.LeftDistance.X, (leftDistance - offset), DeltaTime, InterpSpeed);
	Data.RightDistance.X = UKismetMathLibrary::FInterpTo(Data.RightDistance.X, -(rightDistance - offset), DeltaTime, InterpSpeed);

	Data.LeftRotation = UKismetMathLibrary::RInterpTo(Data.LeftRotation, leftRotation, DeltaTime, InterpSpeed);
	Data.RightRotation = UKismetMathLibrary::RInterpTo(Data.RightRotation, rightRotation, DeltaTime, InterpSpeed);


#ifdef LOG_UCFeetComponent
	CLog::Print(Data.LeftDistance, 11);
	CLog::Print(Data.RightDistance, 12);
	CLog::Print(Data.PelvisDistance, 13);
	CLog::Print(Data.LeftRotation, 14);
	CLog::Print(Data.RightRotation, 15);
#endif
}

void UCFeetComponent::Trace(FName InName, float& OutDistance, FRotator& OutRotation)
{
	FVector socket = OwnerCharacter->GetMesh()->GetSocketLocation(InName);

	float z = OwnerCharacter->GetActorLocation().Z;

	FVector start = FVector(socket.X, socket.Y, z);

	z = start.Z - OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - TraceDistance;
	FVector end = FVector(socket.X, socket.Y, z);

	TArray<AActor*> ignores;
	ignores.Add(OwnerCharacter);

	FHitResult hitResult;
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery1, true, ignores, DrawDebug, hitResult, true, FLinearColor::Green, FLinearColor::Red);

	OutDistance = 0;
	OutRotation = FRotator::ZeroRotator;

	// Hit 지점이 없다면 Return
	CheckFalse(hitResult.bBlockingHit);

	// 발의 실제 위치와 지면 사이의 거리를 계산
	float length = (hitResult.ImpactPoint - hitResult.TraceEnd).Size();
	OutDistance = length + OffsetDistance - TraceDistance;

	// 법선 Vector를 이용해 지면의 기울기 계산
	float roll = UKismetMathLibrary::DegAtan2(hitResult.Normal.Y, hitResult.Normal.Z);
	float pitch = -UKismetMathLibrary::DegAtan2(hitResult.Normal.X, hitResult.Normal.Z);

	OutRotation = FRotator(pitch, 0, roll);
}

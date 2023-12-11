#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IDamage.h"
#include "CKnockDown.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACKnockDown : public AActor
{
	GENERATED_BODY()
	
public:	
	ACKnockDown();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* Collision;

	UPROPERTY(EditAnywhere)
		EAttackType AttackType;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1;

	UPROPERTY(EditAnywhere)
		float DamagePercent;

	UPROPERTY(EditAnywhere)
		FVector LaunchRate;

	UPROPERTY(EditAnywhere)
		FName SocketName;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBoss_Tree.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACBoss_Tree : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBoss_Tree();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* Tree;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* Collision;

public:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		void Explosion();
};

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "N_SpawnActor.generated.h"

UCLASS()
class TOPVIEWPROJECT_API UN_SpawnActor : public UAnimNotify
{
	GENERATED_BODY()

public:
	FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditAnywhere)
		float Spawn_Distance;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> SpawnActor;
};

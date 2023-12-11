#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_LichAttack.generated.h"

UCLASS()
class TOPVIEWPROJECT_API UCAnimNotify_LichAttack : public UAnimNotify
{
	GENERATED_BODY()

public:
	FString GetNotifyName_Implementation() const override;

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditAnywhere)
		FName SocketName;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> SpawnActor;
};

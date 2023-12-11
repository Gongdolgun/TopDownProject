#pragma once

#include "CoreMinimal.h"
#include "Enemy/CEnemy.h"
#include "CEnemy_Skull.generated.h"

UCLASS()
class TOPVIEWPROJECT_API ACEnemy_Skull : public ACEnemy
{
	GENERATED_BODY()

public:
	ACEnemy_Skull();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

//protected:
//	void Hitted() override;
//
//public:
//	void End_Hitted() override;
};

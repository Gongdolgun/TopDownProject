#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDamage.generated.h"

UENUM()
enum class EAttackType : uint8
{
	Stagger = 0, KnockDown, None, 
};

UINTERFACE(MinimalAPI)
class UIDamage : public UInterface
{
	GENERATED_BODY()
};

class TOPVIEWPROJECT_API IIDamage
{
	GENERATED_BODY()

public:
	virtual void BaseAttack(EAttackType InAttackType, AActor* Attacker, float PlayRate, float Damage, FVector LaunchRate);
};
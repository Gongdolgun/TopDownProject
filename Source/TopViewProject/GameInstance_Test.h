#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstance_Test.generated.h"

UCLASS()
class TOPVIEWPROJECT_API UGameInstance_Test : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int DeadEnemy;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Player_HP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Player_MaxHP = 28000;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Player_MP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Player_MaxMP = 3000;

public:
	UPROPERTY(BlueprintReadOnly, Category = "CoolTime")
		float QSkill_MaxCooltime = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CoolTime")
		float QSkill_Cooltime;

	UPROPERTY(BlueprintReadOnly, Category = "CoolTime")
		float WSkill_MaxCooltime = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CoolTime")
		float WSkill_Cooltime;

	UPROPERTY(BlueprintReadOnly, Category = "CoolTime")
		float ESkill_MaxCooltime = 4;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CoolTime")
		float ESkill_Cooltime;

	UPROPERTY(BlueprintReadOnly, Category = "CoolTime")
		float ASkill_MaxCooltime = 7;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CoolTime")
		float ASkill_Cooltime;

	UPROPERTY(BlueprintReadOnly, Category = "CoolTime")
		float SSkill_MaxCooltime = 4;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CoolTime")
		float SSkill_Cooltime;

	UPROPERTY(BlueprintReadOnly, Category = "CoolTime")
		float DSkill_MaxCooltime = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CoolTime")
		float DSkill_Cooltime;

	UPROPERTY(BlueprintReadOnly, Category = "CoolTime")
		float VSkill_MaxCooltime = 30;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CoolTime")
		float VSkill_Cooltime;
};
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Chaos.generated.h"

UCLASS()
class TOPVIEWPROJECT_API UCUserWidget_Chaos : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeOnInitialized() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
public:
	class UProgressBar* ChaosRate;
	class UGameInstance_Test* GameInstance;

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OpenGate();

	UFUNCTION(BlueprintImplementableEvent)
		void OpenGate2();

	UFUNCTION(BlueprintImplementableEvent)
		void Chaos_End();

public:
	void UpdateEnemyRate(int cnt);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int MaxEnemy = 150;

public:
	int DeadEnemy;

	float progressRate;
};

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "CUserWidget_Damage.generated.h"

UCLASS()
class TOPVIEWPROJECT_API UCUserWidget_Damage : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeOnInitialized() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	class UTextBlock* Text_Damage;

public:
	UFUNCTION(BlueprintImplementableEvent)
		void PlayNormalAnim();

	UFUNCTION(BlueprintImplementableEvent)
		void PlayCriticalAnim();

public:
	void changeText(FString InDamage, bool IsCritical);
	void PlayerDamage(FString InDamage);
};

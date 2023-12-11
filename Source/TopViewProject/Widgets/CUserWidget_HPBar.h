#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "CUserWidget_HPBar.generated.h"

UCLASS()
class TOPVIEWPROJECT_API UCUserWidget_HPBar : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeOnInitialized() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	class UProgressBar* HPBar;
};

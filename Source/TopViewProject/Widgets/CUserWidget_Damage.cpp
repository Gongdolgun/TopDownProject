#include "Widgets/CUserWidget_Damage.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Global.h"

void UCUserWidget_Damage::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UCanvasPanel* panel = Cast<UCanvasPanel>(WidgetTree->RootWidget);
	CheckNull(panel);

	TArray<UWidget*> widgets = panel->GetAllChildren();
	for (auto& Widget : widgets)
	{
		Text_Damage = Cast<UTextBlock>(Widget);
		if (Text_Damage == nullptr) continue;
	}
}

void UCUserWidget_Damage::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UCUserWidget_Damage::changeText(FString InDamage, bool IsCritical)
{
	Text_Damage->SetText(FText::FromString(InDamage));

	if(IsCritical == true)
	{
		Text_Damage->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
		PlayCriticalAnim();
	}

	else
	{
		Text_Damage->SetColorAndOpacity(FSlateColor(FLinearColor::White));
		PlayNormalAnim();
	}
}

void UCUserWidget_Damage::PlayerDamage(FString InDamage)
{
	Text_Damage->SetText(FText::FromString(InDamage));

	PlayNormalAnim();
}



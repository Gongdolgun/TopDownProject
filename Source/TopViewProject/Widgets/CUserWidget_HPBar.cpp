#include "Widgets/CUserWidget_HPBar.h"
#include "Global.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ProgressBar.h"

void UCUserWidget_HPBar::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UCanvasPanel* panel = Cast<UCanvasPanel>(WidgetTree->RootWidget);
	CheckNull(panel);

	TArray<UWidget*> widgets = panel->GetAllChildren();
	for(auto& Widget : widgets)
	{
		HPBar = Cast<UProgressBar>(Widget);
		if (HPBar == nullptr) continue;

		//UCanvasPanelSlot* slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(HPBar);
		
	}

	HPBar->SetPercent(1.0f);
}

void UCUserWidget_HPBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

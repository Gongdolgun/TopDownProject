#include "Widgets/CUserWidget_Chaos.h"

#include "GameInstance_Test.h"
#include "Global.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ProgressBar.h"

void UCUserWidget_Chaos::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UCanvasPanel* panel = Cast<UCanvasPanel>(WidgetTree->RootWidget);
	CheckNull(panel);

	TArray<UWidget*> widgets = panel->GetAllChildren();
	for (auto& Widget : widgets)
	{
		ChaosRate = Cast<UProgressBar>(Widget);
		if (ChaosRate == nullptr) continue;
		
	}

	GameInstance = Cast<UGameInstance_Test>(GetGameInstance());
	if (!!GameInstance)
	{
		DeadEnemy = GameInstance->DeadEnemy;
	}

	ChaosRate->SetPercent((float)DeadEnemy / MaxEnemy);
}

void UCUserWidget_Chaos::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UCUserWidget_Chaos::UpdateEnemyRate(int cnt)
{
	GameInstance = Cast<UGameInstance_Test>(GetGameInstance());
	if(!!GameInstance)
	{
		DeadEnemy = GameInstance->DeadEnemy;
	}

	progressRate = (float) DeadEnemy / MaxEnemy;

	ChaosRate->SetPercent(UKismetMathLibrary::FClamp(progressRate, 0, 1));

	if (ChaosRate->Percent > 0.4f && ChaosRate->Percent < 0.49f)
		OpenGate();

	else if (ChaosRate->Percent > 0.8f && ChaosRate->Percent <= 0.9f)
		OpenGate2();

	else if (UKismetMathLibrary::NearlyEqual_FloatFloat(ChaosRate->Percent, 1.f, 0.01f))
		Chaos_End();
}

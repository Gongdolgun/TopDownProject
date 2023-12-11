#include "Enemy/CEnemy_Boss.h"
#include "GameInstance_Test.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"
#include "Widgets/CUserWidget_Damage.h"
#include "Widgets/CUserWidget_Chaos.h"

ACEnemy_Boss::ACEnemy_Boss()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UParticleSystemComponent>(this, &CubeParticle, "CubeParticle", GetMesh());
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &AuraParticle, "AuraParticle", GetMesh());
}

void ACEnemy_Boss::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UGameInstance_Test>(GetGameInstance());
}

void ACEnemy_Boss::BaseAttack(EAttackType InAttackType, AActor* Attacker, float PlayRate, float Damage,
	FVector LaunchRate)
{
	IIDamage::BaseAttack(InAttackType, Attacker, PlayRate, Damage, LaunchRate);
	ACPlayer* Player = Cast<ACPlayer>(Attacker);

	CheckNull(Player);
	CheckTrue(IsDead);


	if (!IsDead)
	{
		HP = UKismetMathLibrary::Clamp(HP - Damage, 0, Max_HP);

		if(HP == 0)
		{
			IsDead = true;
			UnPossessed();
			GameFinish();

			CubeParticle->SetActive(false);
			AuraParticle->SetActive(false);

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			if (!!GameInstance)
				GameInstance->DeadEnemy += 30;

			if (!!Player->WDG_Chaos)
				Player->WDG_Chaos->UpdateEnemyRate(30);
		}

		// Set Damage Widget
		{
			CheckNull(WDG_Damage->GetWidget());

			UCUserWidget_Damage* userwidget_Damage;
			userwidget_Damage = Cast<UCUserWidget_Damage>(WDG_Damage->GetWidget());

			FString damage;
			damage = FString::FormatAsNumber(Damage);

			userwidget_Damage->changeText(damage, Player->bCritical);
		}
	}
}

void ACEnemy_Boss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

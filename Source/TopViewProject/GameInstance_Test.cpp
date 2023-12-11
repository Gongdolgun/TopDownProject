#include "GameInstance_Test.h"
#include "Global.h"

void UGameInstance_Test::Init()
{
	Super::Init();

	Player_HP = Player_MaxHP;
	Player_MP = Player_MaxMP;

	/*QSkill_Cooltime = QSkill_MaxCooltime;
	WSkill_Cooltime = WSkill_MaxCooltime;
	ESkill_Cooltime = ESkill_MaxCooltime;
	ASkill_Cooltime = ASkill_MaxCooltime;
	SSkill_Cooltime = SSkill_MaxCooltime;
	DSkill_Cooltime = DSkill_MaxCooltime;
	VSkill_Cooltime = VSkill_MaxCooltime;*/
}

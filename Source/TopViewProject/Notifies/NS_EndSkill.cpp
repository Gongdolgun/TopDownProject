#include "Notifies/NS_EndSkill.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/CPlayer.h"
#include "Components/CMovementComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CWeaponComponent.h"
#include "Weapon/CWeapon.h"

FString UNS_EndSkill::GetNotifyName_Implementation() const
{
	return "NS_EndSKill";

}

void UNS_EndSkill::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACPlayer* Owner = Cast<ACPlayer>(MeshComp->GetOwner());

	UCWeaponComponent* WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(WeaponComponent);

	UCMovementComponent* MovementComponent = CHelpers::GetComponent<UCMovementComponent>(Owner);
	CheckNull(MovementComponent);

	if (!!Owner)
	{
		Owner->MovementComponent->EnableSprint();

		Owner->Stop();									// �ٴڿ� ���� ������ ����
		WeaponComponent->Weapon->MontageNum = 0;		// �⺻���� ĵ���� �ʿ�
	}
}

void UNS_EndSkill::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);


	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	//ACPlayer* Owner = Cast<ACPlayer>(MeshComp->GetOwner());

	//if(!!Owner )
	//{
	//	Owner->GetCharacterMovement()->MaxWalkSpeed = 600.f;			// �� Default�� �ʱ�ȭ
	//	Owner->GetCharacterMovement()->MaxAcceleration = 2048.f;

	//	Owner->MovementComponent->EnableMove();
	//	Owner->StateComponent->SetIdleMode();
	//}
}

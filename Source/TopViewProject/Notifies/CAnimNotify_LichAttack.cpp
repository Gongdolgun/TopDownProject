#include "Notifies/CAnimNotify_LichAttack.h"
#include "Global.h"
#include "Enemy/CEnemy.h"

FString UCAnimNotify_LichAttack::GetNotifyName_Implementation() const
{
	return "N_LichAttack";
}

void UCAnimNotify_LichAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACEnemy* Owner = Cast<ACEnemy>(MeshComp->GetOwner());
	CheckNull(Owner);

	FActorSpawnParameters param;
	param.Owner = Owner;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnLocation = Owner->GetMesh()->GetSocketLocation(SocketName);

	if (!!SpawnActor)
		Owner->GetWorld()->SpawnActor<AActor>(SpawnActor, SpawnLocation, UKismetMathLibrary::MakeRotFromX(Owner->GetActorForwardVector()), param);
}

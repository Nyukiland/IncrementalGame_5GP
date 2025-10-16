#include "IGGetEnemiesInAreaEffect.h"
#include "IGGameManager.h"
#include "IGStatContainer.h"
#include "Components/InstancedStaticMeshComponent.h"

void UIGGetEnemiesInAreaEffect::InitEffect_Implementation()
{
	Super::InitEffect_Implementation();

	AreaSize = NewObject<UIGStatContainer>(this, AreaSizeSubClass);
	AreaSize->Init();
}

void UIGGetEnemiesInAreaEffect::ApplyEffect_Implementation(FCapacityData& CapacityData)
{
	if (!CapacityData.Manager)
	{
		UE_LOG(LogTemp, Error, TEXT("[IGGetEnemiesInAreaEffect] CapacityData.Manager is not set"));
		return;
	}

	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params;
	Params.bReturnPhysicalMaterial = false;

	GetWorld()->SweepMultiByChannel(
		HitResults,
		CapacityData.CurrentAimPositon,
		CapacityData.CurrentAimPositon,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(AreaSize->CurrentValue),
		Params
	);

	for (const FHitResult& Result : HitResults)
	{
		if (UInstancedStaticMeshComponent* ISM = Cast<UInstancedStaticMeshComponent>(Result.Component))
		{
			int32 InstanceIndex = Result.Item;
			UE_LOG(LogTemp, Log, TEXT("Hit instance %d on %s \n get enemy from instance need to be configured"), InstanceIndex, *ISM->GetName());
		}
	}
}

TArray<UIGStatContainer*> UIGGetEnemiesInAreaEffect::GetStats_Implementation()
{
	TArray<UIGStatContainer*> Stats;
	Stats.Add(AreaSize);
	return Stats;
}

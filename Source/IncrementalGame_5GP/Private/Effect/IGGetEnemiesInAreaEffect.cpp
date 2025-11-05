#include "Effect/IGGetEnemiesInAreaEffect.h"
#include "IGGameManager.h"
#include "IGStatContainer.h"
#include "VectorUtil.h"
#include "CompGeom/FitOrientedBox2.h"
#include "Components/InstancedStaticMeshComponent.h"

void UIGGetEnemiesInAreaEffect::InitEffect_Implementation()
{
	Super::InitEffect_Implementation();

	if (AreaSizeSubClass)
	{
		AreaSize = NewObject<UIGStatContainer>(this, AreaSizeSubClass);
		AreaSize->Init();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[IGGetEnemiesInAreaEffect] AreaSizeSubClass is not set"));
	}
}

void UIGGetEnemiesInAreaEffect::ApplyEffect_Implementation(FCapacityData& CapacityData)
{
	if (!AreaSize)
	{
		UE_LOG(LogTemp, Error, TEXT("[IGGetEnemiesInAreaEffect] AreaSize is not set"));
		return;
	}
	
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
		UInstancedStaticMeshComponent* ISM = Cast<UInstancedStaticMeshComponent>(Result.Component);
		if (!ISM) continue;

		if (!CapacityData.EnemiesIndex.Contains(Result.Item))
		{
			CapacityData.EnemiesIndex.Add(Result.Item);
		}
	}

	CapacityData.LastAreaSize = AreaSize->CurrentValue;
}

TArray<UIGStatContainer*> UIGGetEnemiesInAreaEffect::GetStats_Implementation()
{
	TArray<UIGStatContainer*> Stats;
	Stats.Add(AreaSize);
	return Stats;
}

void UIGGetEnemiesInAreaEffect::ResetEffectCompletly_Implementation()
{
	if (AreaSize)
		AreaSize->ResetStat();
}

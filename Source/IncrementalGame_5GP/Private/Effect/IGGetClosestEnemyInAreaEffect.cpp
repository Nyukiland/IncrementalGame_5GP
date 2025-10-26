#include "Effect/IGGetClosestEnemyInAreaEffect.h"

#include "IGEnemyData.h"
#include "IGGameManager.h"
#include "IGStatContainer.h"
#include "Components/InstancedStaticMeshComponent.h"

void UIGGetClosestEnemyInAreaEffect::InitEffect_Implementation()
{
	if (AreaStatSubClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[GetClosestEnemyInAreaEffect] AreaStatSubClass not properly set"));
		return;
	}
	
	Area = NewObject<UIGStatContainer>(this, AreaStatSubClass);
	Area->Init();
}

void UIGGetClosestEnemyInAreaEffect::ApplyEffect_Implementation(FCapacityData& CapacityData)
{
	if (Area == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[GetClosestEnemyInAreaEffect] AreaStatS not properly set"));
		return;
	}

	if (!CapacityData.Manager)
	{
		UE_LOG(LogTemp, Error, TEXT("[GetClosestEnemyInAreaEffect] CapacityData.Manager is not set"));
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
		FCollisionShape::MakeSphere(Area->CurrentValue),
		Params
	);

	TArray<FEnemyData*> EnemiesInRange;
	
	for (const FHitResult& Result : HitResults)
	{
		UInstancedStaticMeshComponent* ISM = Cast<UInstancedStaticMeshComponent>(Result.Component);
		if (!ISM) continue;

		if (int32* EnemyIndexPtr = CapacityData.Manager->InstanceIdToEnemyIndex.Find(Result.Item))
		{
			FEnemyData& EnemyData = CapacityData.Manager->EnemiesData[*EnemyIndexPtr];
			if (EnemyData.IsActive())
				EnemiesInRange.Add(&EnemyData);
		}
	}
}

TArray<UIGStatContainer*> UIGGetClosestEnemyInAreaEffect::GetStats_Implementation()
{
	TArray<UIGStatContainer*> Stats;
	
	if (Area == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[GetClosestEnemyInAreaEffect] AreaStatS not properly set"));
		return Stats;
	}

	Stats.Add(Area);

	return Stats;
}

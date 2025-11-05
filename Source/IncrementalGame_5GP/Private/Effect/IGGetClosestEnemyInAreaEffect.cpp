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

	int ClosestEnemyIndex = -1;
	float ClosestEnemyDistance = BIG_NUMBER;
	
	for (const FHitResult& Result : HitResults)
	{
		UInstancedStaticMeshComponent* ISM = Cast<UInstancedStaticMeshComponent>(Result.Component);
		if (!ISM) continue;

		float Dist = FVector::Dist(Result.ImpactPoint, CapacityData.CurrentAimPositon);
		
		if (ClosestEnemyIndex == -1 || Dist < ClosestEnemyDistance)
		{
			ClosestEnemyIndex = Result.Item;
			ClosestEnemyDistance = Dist;
		}
	}

	if (ClosestEnemyIndex != -1 && !CapacityData.EnemiesIndex.Contains(ClosestEnemyIndex))
	{
		CapacityData.EnemiesIndex.Add(ClosestEnemyIndex);
		CapacityData.PreviousAimPosition = CapacityData.CurrentAimPositon;
		CapacityData.CurrentAimPositon = CapacityData.Manager->GetEnemy(ClosestEnemyIndex).Transform.GetLocation();
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

void UIGGetClosestEnemyInAreaEffect::ResetEffectCompletly_Implementation()
{
	if (Area)
		Area->ResetStat();
}

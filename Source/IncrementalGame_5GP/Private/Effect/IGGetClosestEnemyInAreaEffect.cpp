#include "Effect/IGGetClosestEnemyInAreaEffect.h"
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

	for (const FHitResult& Result : HitResults)
	{
		if (UInstancedStaticMeshComponent* ISM = Cast<UInstancedStaticMeshComponent>(Result.Component))
		{
			int32 InstanceIndex = Result.Item;
			UE_LOG(LogTemp, Log, TEXT("Hit instance %d on %s \n get enemy from instance need to be configured"), InstanceIndex, *ISM->GetName());
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

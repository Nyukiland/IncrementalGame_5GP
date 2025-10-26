#include "Effect/IGGetEnemiesInAreaEffect.h"
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

TArray<UIGStatContainer*> UIGGetEnemiesInAreaEffect::GetStats_Implementation()
{
	TArray<UIGStatContainer*> Stats;
	Stats.Add(AreaSize);
	return Stats;
}

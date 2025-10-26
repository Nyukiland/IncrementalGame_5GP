#include "Effect/IGGetEnemiesInLineEffect.h"

#include "IGEnemyData.h"
#include "IGGameManager.h"
#include "Components/InstancedStaticMeshComponent.h"

void UIGGetEnemiesInLineEffect::ApplyEffect_Implementation(FCapacityData& CapacityData)
{
	if (!CapacityData.Manager)
	{
		UE_LOG(LogTemp, Error, TEXT("[IGGetEnemiesInLine] CapacityData.Manager is not set"));
		return;
	}

	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params;
	Params.bReturnPhysicalMaterial = false;

	GetWorld()->SweepMultiByChannel(
		HitResults,
		CapacityData.PreviousAimPosition,
		CapacityData.CurrentAimPositon,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(ToleranceRadius),
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

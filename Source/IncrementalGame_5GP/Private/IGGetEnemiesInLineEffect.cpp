#include "IGGetEnemiesInLineEffect.h"
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

	for (const FHitResult& Result : HitResults)
	{
		if (UInstancedStaticMeshComponent* ISM = Cast<UInstancedStaticMeshComponent>(Result.Component))
		{
			int32 InstanceIndex = Result.Item;
			UE_LOG(LogTemp, Log, TEXT("Hit instance %d on %s \n get enemy from instance need to be configured"), InstanceIndex, *ISM->GetName());
		}
	}
}

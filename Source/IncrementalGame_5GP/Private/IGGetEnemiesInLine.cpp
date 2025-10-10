#include "IGGetEnemiesInLine.h"
#include "Components/InstancedStaticMeshComponent.h"

void UIGGetEnemiesInLine::ApplyEffect_Implementation(FCapacityData& CapacityData)
{
	if (!CapacityData.Manager)
	{
		UE_LOG(LogTemp, Error, TEXT("[IGGetEnemiesInLine] CapacityData.Manager is not set"));
		return;
	}

	float Radius = ToleranceRadius;

	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params;
	Params.bReturnPhysicalMaterial = false;

	GetWorld()->SweepMultiByChannel(
		HitResults,
		CapacityData.PreviousAimPosition,
		CapacityData.CurrentAimPositon,
		FQuat::Identity,
		ECC_Pawn,
		FCollisionShape::MakeSphere(Radius),
		Params
	);

	for (const FHitResult& Result : HitResults)
	{
		if (AActor* HitActor = Result.GetActor())
		{
			UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), *HitActor->GetName());
		}

		if (UInstancedStaticMeshComponent* ISM = Cast<UInstancedStaticMeshComponent>(Result.Component))
		{
			int32 InstanceIndex = Result.Item;
			UE_LOG(LogTemp, Log, TEXT("Hit instance %d on %s"), InstanceIndex, *ISM->GetName());
		}
	}
}

#include "Effect/IGProjectileLineEffect.h"

#include "IGProjectileManagerComponent.h"

void UIGProjectileLineEffect::ApplyEffect_Implementation(FCapacityData& CapacityData)
{
	Super::ApplyEffect_Implementation(CapacityData);

	if (!CapacityData.ProjectileManager)
	{
		UE_LOG(LogTemp, Error, TEXT("[IGProjectileAreaEffect] ProjectileManager is null!"));
		return;
	}

	if (CapacityData.CurrentAimPositon == CapacityData.PreviousAimPosition)
		return;
	
	CapacityData.ProjectileManager->AddProjectile(CapacityData.PreviousAimPosition, ProjectileSize,
		CapacityData.CurrentAimPositon, ProjectileTime, ProjectileHold, Color); 
}

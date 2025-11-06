#include "Effect/IGStandardProjectileEffect.h"

#include "IGProjectileManagerComponent.h"

void UIGStandardProjectileEffect::ApplyEffect_Implementation(FCapacityData& CapacityData)
{
	Super::ApplyEffect_Implementation(CapacityData);

	if (!CapacityData.ProjectileManager)
	{
		UE_LOG(LogTemp, Error, TEXT("[IGStandardProjectileEffect] ProjectileManager is null!"));
		return;
	}

	if (CapacityData.PreviousAimPosition == CapacityData.CurrentAimPositon)
		return;
	
	CapacityData.ProjectileManager->AddProjectile(CapacityData.PreviousAimPosition, CapacityData.CurrentAimPositon,
		ProjectileSize, ProjectileTime, 0, Color); 
}

#include "Effect/IGProjectileAreaEffect.h"

#include "IGProjectileManagerComponent.h"

void UIGProjectileAreaEffect::ApplyEffect_Implementation(FCapacityData& CapacityData)
{
	Super::ApplyEffect_Implementation(CapacityData);

	if (!CapacityData.ProjectileManager)
	{
		UE_LOG(LogTemp, Error, TEXT("[IGProjectileAreaEffect] ProjectileManager is null!"));
		return;
	}

	CapacityData.ProjectileManager->AddProjectile(CapacityData.CurrentAimPositon, CapacityData.LastAreaSize,
		ProjectileTime, ProjectileHold, Color); 
}

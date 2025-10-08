#include "IGGetEnemiesInAreaEffect.h"
#include "IGGameManager.h"

void UIGGetEnemiesInAreaEffect::ApplyEffect_Implementation(FCapacityData& CapacityData)
{
	if (!CapacityData.Manager)
	{
		UE_LOG(LogTemp, Error, TEXT("[IGGetEnemiesInAreaEffect] CapacityData.Manager is not set"));
		return;
	}

	//TO DO
}

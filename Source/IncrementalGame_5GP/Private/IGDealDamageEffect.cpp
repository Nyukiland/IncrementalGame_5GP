#include "IGDealDamageEffect.h"
#include "IGGameManager.h"
#include "IGStatContainer.h"

void UIGDealDamageEffect::ApplyEffect_Implementation(FCapacityData& CapacityData)
{
	if (!CapacityData.Manager)
	{
		UE_LOG(LogTemp, Error, TEXT("[IGDealDamageEffect] CapacityData.Manager is not set"));
		return;
	}
	
	if (CapacityData.EnemiesIndex.Num() == 0)
	{
		return;
	}

	for (int Index : CapacityData.EnemiesIndex)
	{
		CapacityData.Manager->GetEnemy(Index).ApplyDamage(DamageStat->CurrentValue);
	}
}

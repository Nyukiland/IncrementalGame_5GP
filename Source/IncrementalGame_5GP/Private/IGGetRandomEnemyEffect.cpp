#include "IGGetRandomEnemyEffect.h"
#include "IGGameManager.h"

void UIGGetRandomEnemyEffect::ApplyEffect_Implementation(FCapacityData& CapacityData)
{
	if (!CapacityData.Manager)
	{
		UE_LOG(LogTemp, Error, TEXT("[IGGetRandomEnemyEffect] CapacityData.Manager is not set"));
		return;
	}

	int EnemyIndex = CapacityData.Manager->GetRandomEnemy();

	if (CapacityData.EnemiesIndex.Contains(EnemyIndex))
	{
		return;
	}
	
	CapacityData.PreviousAimPosition = CapacityData.CurrentAimPositon;
	CapacityData.CurrentAimPositon = CapacityData.Manager->GetEnemy(EnemyIndex).Transform.GetLocation();

	CapacityData.EnemiesIndex.Add(EnemyIndex);
}

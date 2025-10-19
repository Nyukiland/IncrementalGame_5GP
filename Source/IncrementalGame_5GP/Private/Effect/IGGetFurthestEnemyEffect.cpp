#include "Effect/IGGetFurthestEnemyEffect.h"
#include "IGGameManager.h"

void UIGGetFurthestEnemyEffect::ApplyEffect_Implementation(FCapacityData& CapacityData)
{
	if (!CapacityData.Manager)
	{
		UE_LOG(LogTemp, Error, TEXT("[IGGetFurthestEnemyEffect] CapacityData.Manager is not set"));
		return;
	}

	int EnemyIndex = CapacityData.Manager->GetFarthestEnemy();

	if (CapacityData.EnemiesIndex.Contains(EnemyIndex))
	{
		return;
	}
	
	CapacityData.PreviousAimPosition = CapacityData.CurrentAimPositon;
	CapacityData.CurrentAimPositon = CapacityData.Manager->GetEnemy(EnemyIndex).Transform.GetLocation();

	CapacityData.EnemiesIndex.Add(EnemyIndex);
}

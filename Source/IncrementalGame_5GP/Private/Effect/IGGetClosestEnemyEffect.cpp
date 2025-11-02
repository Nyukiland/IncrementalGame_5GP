#include "Effect/IGGetClosestEnemyEffect.h"
#include "IGGameManager.h"
#include "IGProjectileManagerComponent.h"

void UIGGetClosestEnemyEffect::ApplyEffect_Implementation(FCapacityData& CapacityData)
{
	if (!CapacityData.Manager)
	{
		UE_LOG(LogTemp, Error, TEXT("[IGGetClosestEnemyEffect] CapacityData.Manager is not set"));
		return;
	}

	int EnemyIndex = CapacityData.Manager->GetClosestEnemy();
	
	if (EnemyIndex == -1 || CapacityData.EnemiesIndex.Contains(EnemyIndex))
		return;
	
	CapacityData.PreviousAimPosition = CapacityData.CurrentAimPositon;
	CapacityData.CurrentAimPositon = CapacityData.Manager->GetEnemy(EnemyIndex).Transform.GetLocation();

	CapacityData.EnemiesIndex.Add(EnemyIndex);
}

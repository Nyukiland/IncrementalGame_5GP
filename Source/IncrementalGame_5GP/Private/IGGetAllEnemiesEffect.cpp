#include "IGGetAllEnemiesEffect.h"
#include "IGGameManager.h"

void UIGGetAllEnemiesEffect::ApplyEffect_Implementation(FCapacityData& CapacityData)
{
	Super::ApplyEffect_Implementation(CapacityData);

	if (CapacityData.Manager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[GetAllEnemiesEffect] Manager is not set in the data"));
		return;
	}

	for (int Enemy : CapacityData.Manager->ActiveEnemiesIndices)
	{
		if (CapacityData.EnemiesIndex.Contains(Enemy))
			continue;

		CapacityData.EnemiesIndex.Add(Enemy);
	}
}

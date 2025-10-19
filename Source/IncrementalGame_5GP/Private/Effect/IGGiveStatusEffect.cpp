#include "Effect/IGGiveStatusEffect.h"
#include "IGGameManager.h"
#include "IGStatContainer.h"

void UIGGiveStatusEffect::ApplyEffect_Implementation(FCapacityData& CapacityData)
{
	if (!CapacityData.Manager)
	{
		UE_LOG(LogTemp, Error, TEXT("[IGGiveStatusEffect] CapacityData.Manager is not set"));
		return;
	}
	
	for (int Index : CapacityData.EnemiesIndex)
	{
		FStatus NewStatus = FStatus(StatusToGive);
		NewStatus.InitStatus();
		
		CapacityData.Manager->GetEnemy(Index).AddStatus(NewStatus);
	}
}
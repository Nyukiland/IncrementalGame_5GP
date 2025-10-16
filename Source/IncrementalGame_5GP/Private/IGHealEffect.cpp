#include "IGHealEffect.h"
#include "IGGameManager.h"
#include "IGStatContainer.h"

void UIGHealEffect::InitEffect_Implementation()
{
	Super::InitEffect_Implementation();

	HealStat = NewObject<UIGStatContainer>(this, HealStatSubClass);
	HealStat->Init();
}

void UIGHealEffect::ApplyEffect_Implementation(FCapacityData& CapacityData)
{
	if (HealStat == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[HealEffect] HealStat not properly set"));
		return;
	}

	if (CapacityData.Manager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[HealEffect] Manager is not set in the data"));
		return;
	}
	
	CapacityData.Manager->ChangeZoneSize(HealStat->CurrentValue);
}

TArray<UIGStatContainer*> UIGHealEffect::GetStats_Implementation()
{
	TArray<UIGStatContainer*> Stats;
	Stats.Add(HealStat);
	
	return Stats;
}

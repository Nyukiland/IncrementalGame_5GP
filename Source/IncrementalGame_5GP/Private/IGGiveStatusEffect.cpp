#include "IGGiveStatusEffect.h"
#include "IGGameManager.h"
#include "IGStatContainer.h"

void UIGGiveStatusEffect::InitEffect_Implementation()
{
	Super::InitEffect_Implementation();

	DamageStat = NewObject<UIGStatContainer>(this, DamageStatSubClass);
	DamageStat->Init();
	
	SlowEffectStat = NewObject<UIGStatContainer>(this, SlowEffectStatSubClass);
	SlowEffectStat->Init();
	
	DurationStat = NewObject<UIGStatContainer>(DurationStatSubClass);
	DurationStat->Init();
	
	TimeBetweenShotsStat = NewObject<UIGStatContainer>(TimeBetweenShotsStatSubClass);
	TimeBetweenShotsStat->Init();
}

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
		NewStatus.InitStatus(DamageStat->CurrentValue, SlowEffectStat->CurrentValue,
			DurationStat->CurrentValue, TimeBetweenShotsStat->CurrentValue);
		
		CapacityData.Manager->GetEnemy(Index).AddStatus(NewStatus);
	}
}

TArray<UIGStatContainer*> UIGGiveStatusEffect::GetStats_Implementation()
{
	TArray<UIGStatContainer*> Stats;

	Stats.Add(DamageStat);
	Stats.Add(DurationStat);
	Stats.Add(SlowEffectStat);
	Stats.Add(TimeBetweenShotsStat);

	return Stats;
}
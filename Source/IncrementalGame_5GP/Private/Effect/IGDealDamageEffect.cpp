#include "Effect/IGDealDamageEffect.h"
#include "IGGameManager.h"
#include "IGStatContainer.h"

void UIGDealDamageEffect::InitEffect_Implementation()
{
	Super::InitEffect_Implementation();

	DamageStat = NewObject<UIGStatContainer>(this, DamageStatSubClass);
	DamageStat->Init();
}

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

TArray<UIGStatContainer*> UIGDealDamageEffect::GetStats_Implementation()
{
	TArray<UIGStatContainer*> Stats;

	Stats.Add(DamageStat);

	return Stats;
}

void UIGDealDamageEffect::ResetEffectCompletly_Implementation()
{
	if (DamageStat)
		DamageStat->ResetStat();
}

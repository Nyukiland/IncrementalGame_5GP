#include "Effect/IGCombinedEffect.h"
#include "Effect/IGRepeatEffect.h"

void UIGCombinedEffect::InitEffect_Implementation()
{
	Super::InitEffect_Implementation();

	for (auto EffectSubClass : EffectSubClasses)
	{
		if (!EffectSubClass)
			continue;

		if (EffectSubClass == StaticClass()
			|| EffectSubClass == UIGRepeatEffect::StaticClass())
		{
			UE_LOG(LogTemp, Error, TEXT(
				       "[CombinedEffect] Please do not set a RepeatEffect or a CombineEffect in a combined effect"));
			continue;
		}

		UIGCapacityEffect* Effect = NewObject<UIGCapacityEffect>(this, EffectSubClass);
		Effect->Duration = Duration;
		Effect->InitEffect();
		Effects.Add(Effect);
	}
}

void UIGCombinedEffect::ApplyEffect_Implementation(FCapacityData& CapacityData)
{
	Super::ApplyEffect_Implementation(CapacityData);

	if (LocalCapacityData.Manager == nullptr)
		LocalCapacityData = CapacityData;

	LocalCapacityData.ResetData();

	for (UIGCapacityEffect* Effect : Effects)
	{
		if (!Effect)
			continue;

		Effect->Timer = Timer;
		Effect->ApplyEffect(LocalCapacityData);
	}

	if (LocalCapacityData.PreviousAimPosition != FVector::ZeroVector)
		CapacityData.PreviousAimPosition = LocalCapacityData.PreviousAimPosition;

	if (LocalCapacityData.CurrentAimPositon != FVector::ZeroVector)
		CapacityData.CurrentAimPositon = LocalCapacityData.CurrentAimPositon;

	if (LocalCapacityData.EnemiesIndex.Num() != 0)
		CapacityData.EnemiesIndex.Append(LocalCapacityData.EnemiesIndex);
}

TArray<UIGStatContainer*> UIGCombinedEffect::GetStats_Implementation()
{
	TArray<UIGStatContainer*> Stats;

	for (UIGCapacityEffect* Effect : Effects)
	{
		if (!Effect)
			continue;

		Stats.Append(Effect->GetStats());
	}

	return Stats;
}

void UIGCombinedEffect::ResetEffectCompletly_Implementation()
{
	for (UIGCapacityEffect* Effect : Effects)
	{
		if (Effect)
			Effect->ResetEffectCompletly();
	}
}

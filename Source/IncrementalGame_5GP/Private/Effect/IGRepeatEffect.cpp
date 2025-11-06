#include "Effect/IGRepeatEffect.h"
#include "Effect/IGCombinedEffect.h"
#include "IGStatContainer.h"
#include "IGGameManager.h"

void UIGRepeatEffect::InitEffect_Implementation()
{
	Super::InitEffect_Implementation();

	if (!RepeatStatSubClass)
	{
		UE_LOG(LogTemp, Error, TEXT("[RepeatEffect] RepeatStatSubClass is not set"))
		return;
	}
	
	RepeatStat = NewObject<UIGStatContainer>(this, RepeatStatSubClass);
	RepeatStat->Init();

	for (auto EffectSubClass : EffectsSubClass)
	{
		if (!EffectSubClass)
			continue;

		if (EffectSubClass == StaticClass()
			|| EffectSubClass == UIGCombinedEffect::StaticClass())
		{
			UE_LOG(LogTemp, Error, TEXT(
				"[RepeatEffect] Please do not set a RepeatEffect or a CombineEffect in a loop effect"));
			continue;
		}
		
		UIGCapacityEffect* Effect = NewObject<UIGCapacityEffect>(this, EffectSubClass);
		Effect->InitEffect();
		Effects.Add(Effect);
	}
	
	Duration = BIG_NUMBER;
	Duration--;
	Timer = 0;
}

void UIGRepeatEffect::ApplyEffect_Implementation(FCapacityData& CapacityData)
{
	if (!RepeatStat)
	{
		UE_LOG(LogTemp, Error, TEXT("[RepeatEffect] RepeatStat is not set"))
		Timer = BIG_NUMBER;
		return;
	}
	
	if (ExecuteEffect(CapacityData))
	{
		if (LoopIndex >= RepeatStat->CurrentValue)
		{
			Timer = BIG_NUMBER;
			LoopIndex = 0;
		}
		else
			LoopIndex++;
		
		for (UIGCapacityEffect* Effect : Effects)
		{
			Effect->Timer = -1;
		}
	}
}

TArray<UIGStatContainer*> UIGRepeatEffect::GetStats_Implementation()
{
	TArray<UIGStatContainer*> Stats;

	if (!RepeatStat)
	{
		UE_LOG(LogTemp, Error, TEXT("[RepeatEffect] RepeatStat is not set"))
		return Stats;
	}
	
	Stats.Add(RepeatStat);
	
	for (UIGCapacityEffect* Effect : Effects)
	{
		if (!Effect)
		{
			continue;
		}

		Stats.Append(Effect->GetStats());
	}

	return Stats;
}

void UIGRepeatEffect::ResetEffectCompletly_Implementation()
{
	if (RepeatStat)
		RepeatStat->ResetStat();

	for (UIGCapacityEffect* Effect : Effects)
	{
		if (Effect)
		Effect->ResetEffectCompletly();
	}
}

bool UIGRepeatEffect::ExecuteEffect(FCapacityData& CapacityData)
{
	int ValidEffectCount = 0;
	float DeltaTime = 0.016f;

	if (CapacityData.Manager)
	{
		DeltaTime = CapacityData.Manager->GetWorld()->GetDeltaSeconds();
	}

	for (UIGCapacityEffect* Effect : Effects)
	{
		if (!Effect || Effect->Timer >= Effect->Duration)
		{
			ValidEffectCount++;
			continue;
		}

		if (Effect->Timer == -1)
			Effect->Timer = 0;
		else
			Effect->Timer += DeltaTime;

		Effect->ApplyEffect(CapacityData);
		return false;
	}

	return ValidEffectCount == Effects.Num();
}

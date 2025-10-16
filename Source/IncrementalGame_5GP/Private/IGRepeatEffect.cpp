#include "IGRepeatEffect.h"
#include "IGGameManager.h"
#include "IGStatContainer.h"

void UIGRepeatEffect::InitEffect_Implementation()
{
	Super::InitEffect_Implementation();
	
	RepeatStat = NewObject<UIGStatContainer>(this, RepeatStatSubClass);
	RepeatStat->Init();

	for (auto EffectSubClass : EffectsSubClass)
	{
		if (!EffectSubClass)
			continue;
		
		UIGCapacityEffect* Effect = NewObject<UIGCapacityEffect>(this, EffectSubClass);
		Effect->InitEffect();
		Effects.Add(Effect);
	}
}

void UIGRepeatEffect::ApplyEffect_Implementation(FCapacityData& CapacityData)
{
	//Ugly sorry
	bWaitToBeComplete = true;
	Duration = BIG_NUMBER;
	
	if (ExecuteEffect(CapacityData))
	{
		Timer = BIG_NUMBER;
	}
}

TArray<UIGStatContainer*> UIGRepeatEffect::GetStats_Implementation()
{
	TArray<UIGStatContainer*> Stats;
	
	for (UIGCapacityEffect* Effect : Effects)
	{
		if (!Effect)
		{
			continue;
		}
		
		if (Cast<UIGRepeatEffect>(Effect))
		{
			UE_LOG(LogTemp, Error, TEXT("[IGRepeatEffect] Do not loop effect in another loop"));
			continue;
		}

		Stats.Append(Effect->GetStats());
	}

	return Stats;
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

		if (Effect->bWaitToBeComplete)
			return false;
	}

	return ValidEffectCount == Effects.Num();
}
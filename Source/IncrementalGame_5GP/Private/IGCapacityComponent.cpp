#include "IGCapacityComponent.h"
#include "IGCapacityTrigger.h"
#include "IGCapacityEffect.h"

bool UIGCapacityComponent::CheckValidity()
{
	if (Triggers.Num() == 0 || Effects.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Wrong set up on %s"), *this->GetName());
		return false;
	}

	return true;
}

void UIGCapacityComponent::ExecuteEffect()
{
	if (!CheckValidity())
		return;

	AActor* Source = GetTypedOuter<AActor>();

	for (UIGCapacityEffect* Effect : Effects)
	{
		if (!Effect) continue;
		Effect->ApplyEffect(Source, nullptr);
	}
}

bool UIGCapacityComponent::CheckTriggers()
{
	int TriggerCount = 0;
	int TriggerValid = 0;
	
	for (UIGCapacityTrigger* Trigger : Triggers)
	{
		if (!Trigger) continue;

		TriggerCount++;
		if (Trigger->bTriggerReady) TriggerValid++;
	}

	return TriggerValid == TriggerCount;
}

void UIGCapacityComponent::EnableStateComponent_Implementation()
{
	
}

void UIGCapacityComponent::DisableStateComponent_Implementation()
{

}

void UIGCapacityComponent::TickStateComponent_Implementation(float DeltaTime)
{
	if (!CheckValidity())
		return;

	for (UIGCapacityTrigger* Trigger : Triggers)
	{
		if (!Trigger) continue;
		Trigger->TickTrigger(DeltaTime);
	}

	if (CheckTriggers())
	{
		ExecuteEffect();
		for (UIGCapacityTrigger* Trigger : Triggers)
		{
			if (!Trigger) continue;
			Trigger->ResetTrigger();
		}
	}
}
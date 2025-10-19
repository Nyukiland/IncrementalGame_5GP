#include "IGCapacityComponent.h"
#include "Trigger/IGCapacityTrigger.h"
#include "Effect/IGCapacityEffect.h"
#include "IGGameManager.h"
#include "IGPlayer.h"

bool UIGCapacityComponent::CheckValidity()
{
	if (Triggers.Num() == 0 || Effects.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Wrong set up on %s"), *this->GetName());
		return false;
	}

	return true;
}

bool UIGCapacityComponent::ExecuteEffect(float DeltaTime)
{
	if (!CheckValidity())
		return false;

	int ValidEffectCount = 0;

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

bool UIGCapacityComponent::CheckTriggers(float DeltaTime)
{
	if (!CheckValidity())
		return false;

	int TriggerValid = 0;

	for (UIGCapacityTrigger* Trigger : Triggers)
	{
		if (!Trigger || Trigger->bTriggerReady)
		{
			TriggerValid++;
			continue;
		}

		Trigger->TickTrigger(DeltaTime);
	}

	return TriggerValid == Triggers.Num();
}

void UIGCapacityComponent::InitStateComponent_Implementation(AIGPlayer* Controller)
{
	Super::InitStateComponent_Implementation(Controller);

	Triggers.Empty();
	Effects.Empty();

	for (auto TriggerClass : TriggersSubClass)
	{
		if (!TriggerClass)
			continue;

		UIGCapacityTrigger* Trigger = NewObject<UIGCapacityTrigger>(this, TriggerClass);
		Trigger->InitTrigger();
		Triggers.Add(Trigger);
	}

	for (auto EffectClass : EffectsSubClass)
	{
		if (!EffectClass)
			continue;
		UIGCapacityEffect* Effect = NewObject<UIGCapacityEffect>(this, EffectClass);
		Effect->InitEffect();
		Effects.Add(Effect);
	}

	CapacityData.Manager = Controller->GetWorld()->GetSubsystem<UIGGameManager>();
	CapacityData.Player = Controller;
}

void UIGCapacityComponent::EnableStateComponent_Implementation()
{
	CapacityData.ResetData();
}

void UIGCapacityComponent::DisableStateComponent_Implementation()
{
}

void UIGCapacityComponent::TickStateComponent_Implementation(float DeltaTime)
{
	if (!CheckValidity())
		return;

	if (CheckTriggers(DeltaTime))
	{
		if (ExecuteEffect(DeltaTime))
		{
			for (UIGCapacityTrigger* Trigger : Triggers)
			{
				if (!Trigger) continue;
				Trigger->ResetTrigger();
			}

			for (UIGCapacityEffect* Effect : Effects)
			{
				Effect->Timer = -1;
			}

			CapacityData.ResetData();
		}
	}
}

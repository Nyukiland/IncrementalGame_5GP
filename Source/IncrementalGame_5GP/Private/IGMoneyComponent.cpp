#include "IGMoneyComponent.h"

void UIGMoneyComponent::DisableStateComponent_Implementation()
{
	Super::DisableStateComponent_Implementation();
	Money = 0;
}

void UIGMoneyComponent::GiveMoney(int NewAmount)
{
	Money += NewAmount;
}

void UIGMoneyComponent::RemoveMoney(int DelAmount)
{
	Money -= DelAmount;
	if (Money < 0)
		Money = 0;
}

bool UIGMoneyComponent::HasEnoughMoney(int Amount)
{
	return Amount >= 0 && Money >= Amount;
}

bool UIGMoneyComponent::TryBuy(int Amount)
{
	if (HasEnoughMoney(Amount))
	{
		RemoveMoney(Amount);
		return true;
	}
	
	return false;
}

#include "IGStatContainer.h"

void UIGStatContainer::Init()
{
	if (!UpgradeEquationSubClass || !PriceEquationSubClass)
	{
		UE_LOG(LogTemp, Error, TEXT("[IGStatContainer] SubClass not properly set on: %s"), *GetName())
		return;
	}
	
	UpgradeEquation = NewObject<UIGMathEquations>(this, UpgradeEquationSubClass);

	PriceEquation = NewObject<UIGMathEquations>(this, PriceEquationSubClass);

	CurrentPrice = PriceEquation->GetValue(0);
	CurrentValue = UpgradeEquation->GetValue(0);
}

bool UIGStatContainer::CheckIfCanUpgrade(int Money)
{
	return Money >= CurrentPrice;;
}

void UIGStatContainer::Upgrade()
{
	CurrentUpgradeCount++;
	CurrentPrice = PriceEquation->GetValue(CurrentUpgradeCount);
	CurrentValue = UpgradeEquation->GetValue(CurrentUpgradeCount);
}

bool UIGStatContainer::TryUpgrade(int Money)
{
	if (CheckIfCanUpgrade(Money))
	{
		Upgrade();
		return true;
	}
	
	return false;
}

void UIGStatContainer::ResetStat()
{
	CurrentUpgradeCount = 0;
	CurrentPrice = PriceEquation->GetValue(CurrentUpgradeCount);
	CurrentValue = UpgradeEquation->GetValue(CurrentUpgradeCount);
}

#include "IGStatContainer.h"

void UIGStatContainer::Init()
{
	UpgradeEquation = NewObject<UIGMathEquations>(this, UpgradeEquationSubClass);

	PriceEquation = NewObject<UIGMathEquations>(this, PriceEquationSubClass);
}

bool UIGStatContainer::CheckIfCanUpgrade(float Money)
{
	return false;
}

void UIGStatContainer::Upgrade()
{
	
}

bool UIGStatContainer::TryUpgrade(float Money)
{
	return false;
}
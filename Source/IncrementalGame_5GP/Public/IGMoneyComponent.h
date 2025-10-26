#pragma once

#include "CoreMinimal.h"
#include "IGStateComponent.h"
#include "IGMoneyComponent.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGMoneyComponent : public UIGStateComponent
{
	GENERATED_BODY()

private:
	int Money;

public:
	virtual void DisableStateComponent_Implementation() override;
	void GiveMoney(int NewAmount);
	void RemoveMoney(int DelAmount);
	bool HasEnoughMoney(int Amount);
	bool TryBuy(int Amount);
};

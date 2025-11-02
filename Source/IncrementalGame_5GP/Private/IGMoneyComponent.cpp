#include "IGMoneyComponent.h"

#include "IGGameManager.h"
#include "IGPlayer.h"
#include "IGStatContainer.h"

void UIGMoneyComponent::InitStateComponent_Implementation(AIGPlayer* Controller)
{
	Super::InitStateComponent_Implementation(Controller);

	Controller->GetWorld()->GetSubsystem<UIGGameManager>()->OnEnemyDeath.AddDynamic(this, &UIGMoneyComponent::OnEnemyDeath);


	if (MoneyPerKillSubClass)
	{
	MoneyPerKill = NewObject<UIGStatContainer>(this, MoneyPerKillSubClass);
	MoneyPerKill->Init();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[IGMoneyComponent] MoneyPerKillSubClass is not set up"));			
	}
}

void UIGMoneyComponent::ResetComponent_Implementation()
{
	Super::ResetComponent_Implementation();

	Money = 0;
}

int UIGMoneyComponent::CurrentMoney()
{
	return Money;
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

void UIGMoneyComponent::OnEnemyDeath(const FVector& DeathTransform)
{
	if (!MoneyPerKill)
		UE_LOG(LogTemp, Error, TEXT("[IGMoneyComponent] MoneyPerKillSubClass is not set up"));
	
	GiveMoney(MoneyPerKill->CurrentValue);
}

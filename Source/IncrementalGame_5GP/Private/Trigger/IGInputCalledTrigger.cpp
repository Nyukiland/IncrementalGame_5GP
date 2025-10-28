#include "Trigger/IGInputCalledTrigger.h"

#include "IGPlayer.h"

void UIGInputCalledTrigger::InitTrigger_Implementation(AIGPlayer* Player)
{
	Super::InitTrigger_Implementation(Player);

	Player->OnEventCalled.AddDynamic(this, &UIGInputCalledTrigger::OnEventReceived);
}

void UIGInputCalledTrigger::TickTrigger_Implementation(float DeltaTime)
{
	Super::TickTrigger_Implementation(DeltaTime);

	if (!bTriggerReady)
		return;
	
	ToleranceTimer += DeltaTime;

	if (ToleranceTimer > ToleranceValidity)
	{
		bTriggerReady = false;
		ToleranceValidity = 0;
	}
}

void UIGInputCalledTrigger::ResetTrigger_Implementation()
{
	Super::ResetTrigger_Implementation();
	ToleranceTimer = 0;
	bTriggerReady = false;
}

void UIGInputCalledTrigger::OnEventReceived(const FString& Value)
{
	if (Value == EventChecker)
		bTriggerReady = true;
}

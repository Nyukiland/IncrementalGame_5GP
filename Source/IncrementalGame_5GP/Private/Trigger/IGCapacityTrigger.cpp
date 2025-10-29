#include "Trigger/IGCapacityTrigger.h"

class UIGStatContainer;

void UIGCapacityTrigger::InitTrigger_Implementation(AIGPlayer* Player)
{
	
}

void UIGCapacityTrigger::TickTrigger_Implementation(float DeltaTime)
{

}

void UIGCapacityTrigger::ResetTrigger_Implementation()
{
	bTriggerReady = false;
}

TArray<UIGStatContainer*> UIGCapacityTrigger::GetStats_Implementation()
{
	return TArray<UIGStatContainer*>();
}

void UIGCapacityTrigger::ResetTriggerCompletly_Implementation()
{
	bTriggerReady = false;
}

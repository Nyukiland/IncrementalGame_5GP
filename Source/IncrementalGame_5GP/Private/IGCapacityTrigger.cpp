#include "IGCapacityTrigger.h"

class UIGStatContainer;

void UIGCapacityTrigger::TickTrigger_Implementation(float DeltaTime)
{

}

void UIGCapacityTrigger::ResetTrigger_Implementation()
{
	TriggerReady = false;
}

TArray<UIGStatContainer*> UIGCapacityTrigger::GetStats_Implementation()
{
	return TArray<UIGStatContainer*>();
}
#include "Trigger/IGConstantValidTrigger.h"

void UIGConstantValidTrigger::TickTrigger_Implementation(float DeltaTime)
{
	Super::TickTrigger_Implementation(DeltaTime);
	bTriggerReady = true;
}

void UIGConstantValidTrigger::ResetTrigger_Implementation()
{
	bTriggerReady = true;
}

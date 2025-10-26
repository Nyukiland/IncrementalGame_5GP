#include "Trigger/IGInputCalledTrigger.h"

void UIGInputCalledTrigger::TickTrigger_Implementation(float DeltaTime)
{
	Super::TickTrigger_Implementation(DeltaTime);

	//TO DO
}

void UIGInputCalledTrigger::ResetTrigger_Implementation()
{
	Super::ResetTrigger_Implementation();
	ToleranceTimer = 0;
}

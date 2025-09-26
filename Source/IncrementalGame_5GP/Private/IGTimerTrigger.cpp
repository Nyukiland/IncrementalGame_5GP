#include "IGTimerTrigger.h"
#include "IGStatContainer.h"

void UIGTimerTrigger::TickTrigger_Implementation(float DeltaTime)
{
	Timer += DeltaTime;

	if (Timer >= MaxTimer->CurrentValue)
	{
		bTriggerReady = true;
	}
}

void UIGTimerTrigger::ResetTrigger_Implementation()
{
	Timer = 0;
	bTriggerReady = false;
}

TArray<UIGStatContainer*> UIGTimerTrigger::GetStats_Implementation()
{
	TArray<UIGStatContainer*> Stats;
	Stats.Add(MaxTimer);
	return Stats;
}

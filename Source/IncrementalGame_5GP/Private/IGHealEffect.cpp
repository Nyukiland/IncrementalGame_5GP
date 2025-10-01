#include "IGHealEffect.h"
#include "IGGameManager.h"
#include "IGStatContainer.h"

void UIGHealEffect::ApplyEffect_Implementation(AIGPlayer* Player, FVector Target)
{
	if (HealStat == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[HealEffect] HealStat not properly set"));
		return;
	}
	
	if (Manager == nullptr)
		Manager = Player->GetWorld()->GetSubsystem<UIGGameManager>();

	Manager->ChangeZoneSize(HealStat->CurrentValue);
}

TArray<UIGStatContainer*> UIGHealEffect::GetStats_Implementation()
{
	TArray<UIGStatContainer*> Stats;
	Stats.Add(HealStat);
	
	return Stats;
}

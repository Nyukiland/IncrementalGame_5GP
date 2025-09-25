#include "IGProjectile.h"
#include "IGCapacityEffect.h"

AIGProjectile::AIGProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

bool AIGProjectile::CheckValidity()
{
	if (Effects.Num() == 0)
		return false;

	return true;
}

void AIGProjectile::DoEffects()
{
	if (!CheckValidity())
		return;

	AActor* Source = GetTypedOuter<AActor>();

	for (UIGCapacityEffect* Effect : Effects)
	{
		if (!Effect) continue;
		Effect->ApplyEffect(Source, nullptr);
	}
}
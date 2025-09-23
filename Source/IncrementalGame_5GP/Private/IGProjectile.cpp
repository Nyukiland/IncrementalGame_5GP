#include "IGProjectile.h"

AIGProjectile::AIGProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AIGProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AIGProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
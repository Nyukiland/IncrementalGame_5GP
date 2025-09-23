#include "IGEnemy.h"

AIGEnemy::AIGEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AIGEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AIGEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
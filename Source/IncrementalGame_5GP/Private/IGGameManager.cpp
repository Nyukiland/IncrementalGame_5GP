#include "IGGameManager.h"

AIGGameManager::AIGGameManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AIGGameManager::BeginPlay()
{
	Super::BeginPlay();
}

void AIGGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
#include "IGGameManager.h"

void UIGGameManager::Tick(float DeltaTime)
{
	
}

void UIGGameManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
}

TStatId UIGGameManager::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UIGGameManager, STATGROUP_Tickables);
}

int UIGGameManager::GetFursthestEnemy()
{
	return 0;
}

int UIGGameManager::GetClosestEnemy()
{
	return 0;
}

int UIGGameManager::GetRandomEnemy()
{
	return 0;
}

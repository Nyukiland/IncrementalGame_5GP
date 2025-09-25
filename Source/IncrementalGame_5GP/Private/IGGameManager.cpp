#include "IGGameManager.h"
#include "IGEnemy.h"

void UIGGameManager::Tick(float DeltaTime)
{
	Timer += DeltaTime;

	if (Timer >= CurrentEnemySpawnRate)
	{
		Timer = 0;
		SpawnEnemy();
	}
}

void UIGGameManager::EnemyWentInactive(AIGEnemy* Enemy)
{
	int Index = FindEnemyIndexInList(Enemy);

	if (Index == -1)
	{
		UE_LOG(LogTemp, Error, TEXT("[Game Manager] Index of found Enemy is not valid"));
		return;
	}

	Enemies.Swap(Index, CurrentEnemiesActive-1);
	CurrentEnemiesActive--;
}

void UIGGameManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
}

void UIGGameManager::SpawnEnemy()
{
	if (!EnemyToSpawn)
	{
		UE_LOG(LogTemp, Error, TEXT("[GameManager] EnemyToSpawn is null, can't spawn"));
		return;
	}

	if (CurrentEnemiesActive >= CurrentMaxEnemyCount)
		return;

	if (Enemies.Num() <= CurrentEnemiesActive)
	{
		AIGEnemy* Enemy = GetWorld()->SpawnActor<AIGEnemy>(EnemyToSpawn);
		Enemy->InitEnemy(this);
		Enemies.Add(Enemy);
	}

	FVector Temp = FVector::ZeroVector;
	Enemies[CurrentEnemiesActive]->EnableEnemy(Temp, Temp, 0);
	CurrentEnemiesActive++;
}

int UIGGameManager::FindEnemyIndexInList(AIGEnemy* Enemy, bool bFindInAll, bool bClampToActive)
{
	if (!Enemy)
	{
		UE_LOG(LogTemp, Error, TEXT("[GameManager] Given Enemy to find is invalid"));
		return -1;
	}
	
	int StartIndex = 0;
	int EndIndex = Enemies.Num();
	
	if (bFindInAll && bClampToActive)
		EndIndex = CurrentEnemiesActive;
	else if (!bFindInAll)
		StartIndex = CurrentEnemiesActive;

	if (Enemies.Num() <= StartIndex)
	{
		UE_LOG(LogTemp, Error, TEXT("[GameManager] Start Index is bigger than Enemies count"))
		return -1;
	}

	for (int i = StartIndex; i < EndIndex; i++)
	{
		if (!Enemies[i]) continue;
		
		if (Enemies[i] == Enemy) return i;
	}

	UE_LOG(LogTemp, Error, TEXT("[GameManager] Enemy couldn't be found"))
	return -1;
}

TStatId UIGGameManager::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UIGGameManager, STATGROUP_Tickables);
}
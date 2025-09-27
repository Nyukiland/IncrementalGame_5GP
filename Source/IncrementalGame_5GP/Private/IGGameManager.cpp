#include "IGGameManager.h"
#include "IGEnemyData.h"
#include "Components/InstancedStaticMeshComponent.h"

void UIGGameManager::Tick(float DeltaTime)
{
	if (!EnemiesMeshInstances) return;

	for (FEnemyData& Enemy : EnemiesData)
	{
		if (!Enemy.IsActive()) continue;

		// move enemies here
	}
}

TStatId UIGGameManager::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UIGGameManager, STATGROUP_Tickables);
}

void UIGGameManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
}

void UIGGameManager::InitializeEnemiesMeshInstances(UStaticMesh* Mesh, UMaterialInterface* Material)
{
	if (!GetWorld()) return;

	// The holder contains the EnemiesMeshInstances because the GameManager cannot hold any ActorComponent
	AActor* Holder = GetWorld()->SpawnActor<AActor>(AActor::StaticClass());

	EnemiesMeshInstances = NewObject<UInstancedStaticMeshComponent>(Holder);
	EnemiesMeshInstances->RegisterComponent();
	EnemiesMeshInstances->SetStaticMesh(Mesh);
	if (Material)
	{
		EnemiesMeshInstances->SetMaterial(0, Material);
	}

	Holder->SetRootComponent(EnemiesMeshInstances);
}

int32 UIGGameManager::SpawnEnemy(const FTransform& SpawnTransform)
{
	if (!EnemiesMeshInstances) return INDEX_NONE;

	int32 InstanceId = EnemiesMeshInstances->AddInstance(SpawnTransform);

	FEnemyData NewEnemy;
	NewEnemy.InstanceId = InstanceId;
	NewEnemy.UpdatePosition(SpawnTransform);
	
	EnemiesData.Add(NewEnemy);
	ActiveEnemiesIndices.Add(InstanceId);
	EnemiesPositions.Add(SpawnTransform.GetLocation());
	
	NewEnemy.ActiveEnemiesIndices = &ActiveEnemiesIndices;
	NewEnemy.EnemiesData = &EnemiesData;
	NewEnemy.EnemiesPositions = &EnemiesPositions;
	NewEnemy.GameManager = this;

	InsertIntoGrid(InstanceId, SpawnTransform.GetLocation());

	return InstanceId;
}

FEnemyData* UIGGameManager::GetFarthestEnemy()
{
	if (ActiveEnemiesIndices.Num() == 0) return nullptr;

	FIntPoint StartCell = GetCellCoords(Origin);
	FEnemyData* Farthest = nullptr;
	float MaxDistSq = 0.f;

	const int32 MaxRadius = 50; //arbitrary, needs testing
	for (int32 SearchRadius = MaxRadius; SearchRadius >= 0; --SearchRadius)
	{
		for (int dx = -SearchRadius; dx <= SearchRadius; dx++)
		{
			for (int dy = -SearchRadius; dy <= SearchRadius; dy++)
			{
				if (FMath::Abs(dx) != SearchRadius && FMath::Abs(dy) != SearchRadius)
					continue;

				FIntPoint Cell = StartCell + FIntPoint(dx, dy);
				if (const TArray<int32>* CellArray = Grid.Find(Cell))
				{
					for (int32 EnemyIdx : *CellArray)
					{
						const FVector& Pos = EnemiesPositions[EnemyIdx];
						float DistSq = FVector::DistSquared2D(Pos, Origin);
						if (DistSq > MaxDistSq)
						{
							MaxDistSq = DistSq;
							Farthest = &EnemiesData[EnemyIdx];
						}
					}
				}
			}
		}
	}

	return Farthest;
}

FEnemyData* UIGGameManager::GetClosestEnemy()
{
	if (ActiveEnemiesIndices.Num() == 0) return nullptr;

	FIntPoint StartCell = GetCellCoords(Origin);
	float MinDistSq = TNumericLimits<float>::Max();
	FEnemyData* Closest = nullptr;

	int32 SearchRadius = 0;
	bool bFoundAny = false;

	while (!bFoundAny && SearchRadius < 50)
	{
		for (int dx = -SearchRadius; dx <= SearchRadius; dx++)
		{
			for (int dy = -SearchRadius; dy <= SearchRadius; dy++)
			{
				if (FMath::Abs(dx) != SearchRadius && FMath::Abs(dy) != SearchRadius)
					continue;

				FIntPoint Cell = StartCell + FIntPoint(dx, dy);
				if (const TArray<int32>* CellArray = Grid.Find(Cell))
				{
					for (int32 EnemyIdx : *CellArray)
					{
						const FVector& Pos = EnemiesPositions[EnemyIdx];
						float DistSq = FVector::DistSquared2D(Pos, Origin);
						if (DistSq < MinDistSq)
						{
							MinDistSq = DistSq;
							Closest = &EnemiesData[EnemyIdx];
							bFoundAny = true;
						}
					}
				}
			}
		}
		SearchRadius++;
	}

	return Closest;
}

FEnemyData* UIGGameManager::GetRandomEnemy()
{
	if (ActiveEnemiesIndices.Num() == 0) return nullptr;

	int32 RandomIndex = FMath::RandRange(0, ActiveEnemiesIndices.Num() - 1);
	return &EnemiesData[ActiveEnemiesIndices[RandomIndex]];
}

FIntPoint UIGGameManager::GetCellCoords(const FVector& Pos) const
{
	return FIntPoint(
		FMath::FloorToInt(Pos.X / CellSize),
		FMath::FloorToInt(Pos.Y / CellSize)
	);
}

void UIGGameManager::InsertIntoGrid(int32 EnemyIndex, const FVector& Pos)
{
	FIntPoint Cell = GetCellCoords(Pos);
	Grid.FindOrAdd(Cell).Add(EnemyIndex);
}

void UIGGameManager::RemoveFromGrid(int32 EnemyIndex, const FVector& Pos)
{
	FIntPoint Cell = GetCellCoords(Pos);
	if (TArray<int32>* CellArray = Grid.Find(Cell))
	{
		CellArray->RemoveSwap(EnemyIndex);
		if (CellArray->Num() == 0)
		{
			Grid.Remove(Cell);
		}
	}
}
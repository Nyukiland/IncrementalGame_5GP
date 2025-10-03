#include "Math/UnrealMathUtility.h"
#include "IGGameManager.h"
#include "IGEnemyData.h"
#include "IGMathEquations.h"
#include "IGMathHelper.h"
#include "Components/InstancedStaticMeshComponent.h"

void UIGGameManager::Tick(float DeltaTime)
{
	if (CurrentZoneFrameInvincibility < MaxZoneFrameInvincibility)
		CurrentZoneFrameInvincibility++;
	
	if (!EnemiesMeshInstances) return;

	ClosestEnemyIndex = -1;
	FarthestEnemyIndex = -1;
	float ClosestEnemyDistance = BIG_NUMBER;
	float FarthestEnemyDistance = -1;
	
	for (int i = 0; i < EnemiesData.Num(); i++)
	{
		if (!EnemiesData[i].IsActive()) continue;

		int32 EnemyInstanceId;
		FTransform EnemyTransform;
		float EnemyDistanceFromOrigin;
		EnemiesData[i].UpdatePosition(DeltaTime, EnemyInstanceId, EnemyTransform, EnemyDistanceFromOrigin);
		EnemiesMeshInstances->UpdateInstanceTransform(EnemyInstanceId, EnemyTransform, true, true, true);
		
		if (EnemyDistanceFromOrigin < ClosestEnemyDistance)
		{
			ClosestEnemyDistance = EnemyDistanceFromOrigin;
			ClosestEnemyIndex = i;
		}
		else if (EnemyDistanceFromOrigin > FarthestEnemyDistance)
		{
			FarthestEnemyDistance = EnemyDistanceFromOrigin;
			FarthestEnemyIndex = i;
		}
	}
}

TStatId UIGGameManager::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UIGGameManager, STATGROUP_Tickables);
}

void UIGGameManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	CurrentZoneFrameInvincibility = MaxZoneFrameInvincibility;
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
	FVector BaseDirection = UIGMathHelper::GetRandomPointInCircle();
	NewEnemy.Init(Origin + BaseDirection, EnemyHealth->GetValue(0), BaseDirection, EnemySpeed->GetValue(0));
	EnemiesMeshInstances->UpdateInstanceTransform(NewEnemy.InstanceId, NewEnemy.Transform, true, true, true);

	EnemiesData.Add(NewEnemy);
	ActiveEnemiesIndices.Add(InstanceId);

	NewEnemy.ActiveEnemiesIndices = &ActiveEnemiesIndices;
	NewEnemy.EnemiesData = &EnemiesData;

	return InstanceId;
}

uint32 UIGGameManager::GetFarthestEnemy() const
{
	if (ActiveEnemiesIndices.Num() == 0) return -1;

	return ClosestEnemyIndex;
}

uint32 UIGGameManager::GetClosestEnemy() const
{
	if (ActiveEnemiesIndices.Num() == 0) return -1;

	return FarthestEnemyIndex;
}

uint32 UIGGameManager::GetRandomEnemy() const
{
	if (ActiveEnemiesIndices.Num() == 0) return -1;

	int32 RandomIndex = FMath::RandRange(0, ActiveEnemiesIndices.Num() - 1);
	return RandomIndex;
}

void UIGGameManager::ChangeZoneSize(float ChangeFactor)
{
	if (ChangeFactor < 0)
	{
		if (CurrentZoneFrameInvincibility < MaxZoneFrameInvincibility)
			return;

		CurrentZoneFrameInvincibility = 0;
	}
	
	CurrentZoneRadius += ChangeFactor;

	CurrentZoneRadius = FMath::Clamp(CurrentZoneRadius, MinZoneRadius, MaxZoneRadius);

	if (MinZoneRadius >= CurrentZoneRadius)
	{
		//End Game
	}
}

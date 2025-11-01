#include "IGGameManager.h"
#include "Math/UnrealMathUtility.h"
#include "IGEnemyData.h"
#include "MathEquation/IGMathEquations.h"
#include "IGMathHelper.h"
#include "Components/InstancedStaticMeshComponent.h"

void UIGGameManager::InitializeManager(UInstancedStaticMeshComponent* EnemiesMeshInstancesVar, UIGMathEquations* EnemyLifeVar,
		UIGMathEquations* EnemySpeedVar, UIGMathEquations* EnemySpawnVar, UIGMathEquations* EnemyMaxSpawnVar, UIGMathEquations* ZoneVar)
{
	CurrentZoneFrameInvincibility = MaxZoneFrameInvincibility;

	EnemiesMeshInstances = EnemiesMeshInstancesVar;
	EnemyHealth = EnemyLifeVar;
	EnemySpeed = EnemySpeedVar;
	SpawnRateCurve = EnemySpawnVar;
	MaxSpawnCountCurve = EnemyMaxSpawnVar;
	DecreaseZoneCurve = ZoneVar;

	FString NullParams;

	if (!EnemiesMeshInstances)
		NullParams += TEXT("EnemiesMeshInstances ");
	if (!EnemyHealth)
		NullParams += TEXT("EnemyHealth ");
	if (!EnemySpeed)
		NullParams += TEXT("EnemySpeed ");
	if (!SpawnRateCurve)
		NullParams += TEXT("SpawnRateCurve ");
	if (!MaxSpawnCountCurve)
		NullParams += TEXT("MaxSpawnCountCurve ");
	if (!DecreaseZoneCurve)
		NullParams += TEXT("DecreaseZoneCurve ");

	if (!NullParams.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("[IGGameManager] InitializeManager failed - null parameters: %s"), *NullParams);
	}
}

void UIGGameManager::Tick(float DeltaTime)
{
	if (!bInitialized)
		return;
		
	if (CurrentZoneFrameInvincibility < MaxZoneFrameInvincibility)
		CurrentZoneFrameInvincibility++;

	Timer += DeltaTime;
	TimerScale += DeltaTime;

	if (Timer > 2)
	{
		FTransform Transform;
		Transform.SetScale3D(FVector(1, 1, 1));
		Transform.SetRotation(FQuat(FRotator(0, 0, 0)));
		Transform.SetLocation(FVector(0, 0, 0));
		SpawnEnemy(Transform);
		Timer = 0;	
	}
	
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

int32 UIGGameManager::SpawnEnemy(const FTransform& SpawnTransform)
{
	if (!EnemyHealth || !EnemySpeed)
	{
		UE_LOG(LogTemp, Error, TEXT("[IGGameManager] Can't spawn enemy, Math data not set"));
		return INDEX_NONE;
	}

	if (!EnemiesMeshInstances) return INDEX_NONE;
	
	int32 NewEnemyIndex;
	if (InactiveEnemiesIndices.Num() <= 0)
		// New enemy
		NewEnemyIndex = EnemiesData.AddDefaulted();
	else
		// Pooled enemy
		NewEnemyIndex = InactiveEnemiesIndices.Pop();

	int32 InstanceId = EnemiesMeshInstances->AddInstance(SpawnTransform);
	if (InstanceId < 0)
	{
		// failure, we put the index back into inactives
		if (NewEnemyIndex != INDEX_NONE)
		{
			InactiveEnemiesIndices.Add(NewEnemyIndex);
		}
		return INDEX_NONE;
	}

	FVector BaseDirection = UIGMathHelper::GetRandomPointInCircle();
	FEnemyData& NewEnemyData = EnemiesData[NewEnemyIndex];
	NewEnemyData.ActiveEnemiesIndices = &ActiveEnemiesIndices;
	NewEnemyData.InactiveEnemiesIndices = &InactiveEnemiesIndices;
	NewEnemyData.EnemiesData = &EnemiesData;
	NewEnemyData.Init(Origin + BaseDirection, EnemyHealth->GetValue(TimerScale), BaseDirection,
		EnemySpeed->GetValue(TimerScale), InstanceId);

	EnemiesMeshInstances->UpdateInstanceTransform(InstanceId, NewEnemyData.Transform, true, true, true);
	InstanceIdToEnemyIndex.Add(InstanceId, NewEnemyIndex);

	return InstanceId;
}

void UIGGameManager::KillEnemy(int EnemyIndex)
{
	FEnemyData EnemyToKill = GetEnemy(EnemyIndex);
	int32 InstanceId = EnemyToKill.InstanceId;
	EnemiesMeshInstances->RemoveInstance(EnemyToKill.InstanceId);
	InstanceIdToEnemyIndex.Remove(InstanceId);
	EnemyToKill.Kill();
}

uint32 UIGGameManager::GetFarthestEnemy() const
{
	if (ActiveEnemiesIndices.Num() == 0) return -1;

	return FarthestEnemyIndex;
}

uint32 UIGGameManager::GetClosestEnemy() const
{
	if (ActiveEnemiesIndices.Num() == 0) return -1;

	return ClosestEnemyIndex;
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

void UIGGameManager::ResetManager()
{
	Timer = 0;
	TimerScale = 0;
}
#include "IGGameManager.h"
#include "Math/UnrealMathUtility.h"
#include "IGEnemyData.h"
#include "MathEquation/IGMathEquations.h"
#include "IGMathHelper.h"
#include "Components/InstancedStaticMeshComponent.h"

void UIGGameManager::InitializeManager(UInstancedStaticMeshComponent* EnemiesMeshInstancesVar,
                                       UIGMathEquations* EnemyLifeVar,
                                       UIGMathEquations* EnemySpeedVar, UIGMathEquations* EnemySpawnVar,
                                       UIGMathEquations* ZoneVar,
                                       float ZoneMaxRadiusVar, float ZoneMinRadiusVar, int InvincibilityFrameVar)
{
	EnemiesMeshInstances = EnemiesMeshInstancesVar;
	EnemyHealth = EnemyLifeVar;
	EnemySpeed = EnemySpeedVar;
	SpawnRateCurve = EnemySpawnVar;
	DecreaseZoneCurve = ZoneVar;

	MaxZoneRadius = ZoneMaxRadiusVar;
	MinZoneRadius = ZoneMinRadiusVar;
	MaxZoneFrameInvincibility = InvincibilityFrameVar;

	CurrentZoneFrameInvincibility = MaxZoneFrameInvincibility;
	CurrentZoneRadius = MaxZoneRadius;

	FString NullParams;

	if (!EnemiesMeshInstances)
		NullParams += TEXT("EnemiesMeshInstances ");
	if (!EnemyHealth)
		NullParams += TEXT("EnemyHealth ");
	if (!EnemySpeed)
		NullParams += TEXT("EnemySpeed ");
	if (!SpawnRateCurve)
		NullParams += TEXT("SpawnRateCurve ");
	if (!DecreaseZoneCurve)
		NullParams += TEXT("DecreaseZoneCurve ");

	if (!NullParams.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("[IGGameManager] InitializeManager failed - null parameters: %s"), *NullParams);
		return;
	}

	bInitialized = true;
}

void UIGGameManager::Tick(float DeltaTime)
{
	if (!bInitialized)
		return;

	bool ZoneInvincibility = false;

	if (CurrentZoneFrameInvincibility < MaxZoneFrameInvincibility)
	{
		CurrentZoneFrameInvincibility++;
		ZoneInvincibility = true;
	}

	Timer += DeltaTime;
	TimerScale += DeltaTime;

	if (Timer > SpawnRateCurve->GetValue(TimerScale))
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
		UE_LOG(LogTemp, Error, TEXT("index: %d"), i);
		UE_LOG(LogTemp, Error, TEXT("active: %d"), EnemiesData[i].IsActive());
		UE_LOG(LogTemp, Error, TEXT("dead: %d"), EnemiesData[i].bIsDead);
		
		if (!EnemiesData[i].IsActive())
			continue;

		if (EnemiesData[i].bIsDead)
		{
			OnEnemyDeath.Broadcast(EnemiesData[i].Transform.GetLocation());
			KillEnemy(i);

			continue;
		}

		if (EnemiesData[i].DistanceFromOrigin >= CurrentZoneRadius)
		{
			KillEnemy(i);

			if (!ZoneInvincibility)
			{
				ChangeZoneSize(DecreaseZoneCurve->GetValue(TimerScale));
			}
			continue;
		}

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
	int32 InstanceId;
	if (InactiveEnemiesIndices.Num() <= 0)
	{
		// New enemy
		NewEnemyIndex = EnemiesData.AddDefaulted();
		InstanceId = EnemiesMeshInstances->AddInstance(SpawnTransform);
		EnemiesData[NewEnemyIndex].InstanceId = InstanceId;
		UE_LOG(LogTemp, Error, TEXT("Created Instance Id: %d"), InstanceId);
	}
	else
	{
		// Pooled enemy
		NewEnemyIndex = InactiveEnemiesIndices.Pop();
		InstanceId = EnemiesData[NewEnemyIndex].InstanceId;
		UE_LOG(LogTemp, Error, TEXT("Pooled Instance Id: %d"), InstanceId);
	}

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
	NewEnemyData.Init(FVector::Zero() + BaseDirection, EnemyHealth->GetValue(TimerScale), BaseDirection,
	                  EnemySpeed->GetValue(TimerScale), InstanceId);

	EnemiesMeshInstances->UpdateInstanceTransform(InstanceId, NewEnemyData.Transform, true, true, true);

	return InstanceId;
}

void UIGGameManager::KillEnemy(int EnemyIndex)
{
	UE_LOG(LogTemp, Error, TEXT("EnemyKilled"));

	FTransform HiddenTransform;
	HiddenTransform.SetLocation(FVector(0, 0, -100000.0f));
	HiddenTransform.SetScale3D(FVector::ZeroVector);
	EnemiesMeshInstances->
		UpdateInstanceTransform(EnemiesData[EnemyIndex].InstanceId, HiddenTransform, true, true, true);
	EnemiesData[EnemyIndex].Kill();
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
		OnLoose.Broadcast();
	}
}

void UIGGameManager::ResetManager()
{
	Timer = 0;
	TimerScale = 0;
	CurrentZoneFrameInvincibility = MaxZoneFrameInvincibility;
	CurrentZoneRadius = MaxZoneRadius;

	for (int i = 0; i < EnemiesData.Num(); i++)
	{
		if (!EnemiesData[i].IsActive()) continue;

		KillEnemy(i);
	}
}

#pragma once

#include "CoreMinimal.h"
#include "IGStatus.h"
#include "IGEnemyData.generated.h"

class UIGGameManager;

USTRUCT(BlueprintType)
struct FEnemyData
{
	GENERATED_BODY()

private:
	float Health = 0;
	bool bIsActive_Internal = true;
	FVector Direction = FVector(0, 0, 0);
	float Speed = 0;

public:
	FTransform Transform;
	
	int32 InstanceId = INDEX_NONE;
	float DistanceFromOrigin;

	TArray<int32>* ActiveEnemiesIndices;
	TArray<int32>* InactiveEnemiesIndices;
	TArray<FEnemyData>* EnemiesData;

	TArray<FStatus> Statuses;
	TMap<FName, int> StatusCount;

private:
	void SetActive(bool bNewActive);
	
public:
	void ApplyDamage(float Damage);
	void Death();
	bool IsActive() const { return bIsActive_Internal; }
	void Init(FVector Origin, float BaseHealth, FVector BaseDirection, float BaseSpeed, int32 InstanceId);
	void Kill();
	void UpdatePosition(float DeltaTime, int32& InstanceId, FTransform& Transform, float& EnemyDistanceFromOrigin);
	void AddStatus(FStatus NewStatus);
};
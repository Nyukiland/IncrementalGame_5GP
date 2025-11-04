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
	UPROPERTY()
	FVector Direction = FVector(0, 0, 0);
	float Speed = 0;

	float DamageTimer = 0.25f;
	
public:
	FTransform Transform;
	
	int32 InstanceId = INDEX_NONE;
	float DistanceFromOrigin;

	TArray<int32>* ActiveEnemiesIndices;
	TArray<int32>* InactiveEnemiesIndices;
	TArray<FEnemyData>* EnemiesData;

	UPROPERTY()
	TArray<FStatus> Statuses;
	UPROPERTY()
	TMap<FName, int> StatusCount;

	bool bIsDead = false;

private:
	void SetActive(bool bNewActive);
	
public:
	void ApplyDamage(float Damage);
	bool IsActive() const { return bIsActive_Internal; }
	void Init(FVector Origin, float BaseHealth, FVector BaseDirection, float BaseSpeed, int32 InstanceId);
	void Kill();
	void UpdatePosition(float DeltaTime, int32& InstanceId, FTransform& Transform,
		float& EnemyDistanceFromOrigin, FColor& Color);
	void AddStatus(FStatus NewStatus);
};
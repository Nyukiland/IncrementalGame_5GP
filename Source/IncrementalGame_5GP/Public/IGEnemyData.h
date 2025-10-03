#pragma once

#include "CoreMinimal.h"
#include "IGEnemyData.generated.h"

class UIGGameManager;

USTRUCT(BlueprintType)
struct FEnemyData //can create with a simple var "FEnemyData Enemy"
{
	GENERATED_BODY()

private:
	float Health = 0;
	bool bIsActive_Internal = true;
	FVector Direction;
	float Speed;

public:
	FTransform Transform;
	
	int32 InstanceId = INDEX_NONE;
	float DistanceFromOrigin;

	TArray<int32>* ActiveEnemiesIndices;
	TArray<FEnemyData>* EnemiesData;
	
public:
	void ApplyDamage(float Damage);
	void Death();
	void SetActive(bool bNewActive);
	bool IsActive() const { return bIsActive_Internal; }
	void Init(FVector Origin, float BaseHealth, FVector BaseDirection, float BaseSpeed);
	void UpdatePosition(float DeltaTime, int32& InstanceId, FTransform& Transform, float& EnemyDistanceFromOrigin);
};
#pragma once

#include "CoreMinimal.h"
#include "IGGameManager.h"
#include "IGEnemyData.generated.h"

USTRUCT(BlueprintType)
struct FEnemyData //can create with a simple var "FEnemyData Enemy"
{
	GENERATED_BODY()

private:
	float Life = 0;
	bool bIsActive_Internal = true;
	FTransform Transform;

public:
	
	int32 InstanceId = INDEX_NONE;

	TArray<int32>* ActiveEnemiesIndices;
	TArray<FEnemyData>* EnemiesData;
	TArray<FVector>* EnemiesPositions;
	TWeakObjectPtr<UIGGameManager> GameManager;
	
public:
	void ApplyDamage(float Damage);
	void Death();
	void SetActive(bool bNewActive);
	bool IsActive() const { return bIsActive_Internal; }
	void UpdatePosition(FTransform transform);
	void UpdatePosition(FVector position);
};
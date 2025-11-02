#pragma once

#include "CoreMinimal.h"
#include "IGCapacityData.generated.h"

class UIGProjectileManagerComponent;
class AIGPlayer;
class UIGGameManager;

USTRUCT(Blueprintable)
struct FCapacityData
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capacity")
	FVector CurrentAimPositon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capacity")
	FVector PreviousAimPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capacity")
	float LastAreaSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capacity")
	TArray<int> EnemiesIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capacity")
	TObjectPtr<UIGGameManager> Manager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capacity")
	TObjectPtr<AIGPlayer> Player;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capacity")
	TObjectPtr<UIGProjectileManagerComponent> ProjectileManager;

public:
	void ResetData();
};
#pragma once

#include "CoreMinimal.h"
#include "IGCapacityData.generated.h"

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
	TArray<int> EnemiesIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capacity")
	UIGGameManager* Manager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capacity")
	AIGPlayer* Player;

public:
	void ResetData();
};
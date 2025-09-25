#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "IGGameManager.generated.h"

class AIGEnemy;
class UIGMathEquations;

UCLASS(Blueprintable)
class INCREMENTALGAME_5GP_API UIGGameManager : public UWorldSubsystem, public FTickableGameObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	TObjectPtr<UIGMathEquations> MaxSpawnCountCurve;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	TSubclassOf<AIGEnemy> EnemyToSpawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	TObjectPtr<UIGMathEquations> SpawnRateCurve;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Enemy")
	int CurrentMaxEnemyCount;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Enemy")
	float CurrentEnemySpawnRate;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Enemy")
	TArray<TObjectPtr<AIGEnemy>> Enemies;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Enemy")
	int CurrentEnemiesActive;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Enemy")
	float Timer;

public:	
	virtual void Tick(float DeltaTime) override;
	void EnemyWentInactive(AIGEnemy* Enemy);
	virtual bool IsTickable() const override { return true; }
	virtual TStatId GetStatId() const override;

	
protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

private:
	void SpawnEnemy();
	int FindEnemyIndexInList(AIGEnemy* Enemy, bool bFindInAll = false, bool bClampToActive = false);
};
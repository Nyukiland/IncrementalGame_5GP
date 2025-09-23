#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IGGameManager.generated.h"

class AIGEnemy;
class UIGMathEquations;

UCLASS(Blueprintable)
class INCREMENTALGAME_5GP_API AIGGameManager : public AActor
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
	AIGGameManager();
	virtual void Tick(float DeltaTime) override;
	void EnemyWentInactive(AIGEnemy* Enemy);
	
protected:
	virtual void BeginPlay() override;

private:
	void SpawnEnemy();
	int FindEnemyIndexInList(AIGEnemy* Enemy, bool bFindInAll = false, bool bClampToActive = false);
};
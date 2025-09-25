#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "IGGameManager.generated.h"

class UIGMathEquations;

USTRUCT(BlueprintType)
struct FEnemyData //can create with a simple var "FEnemyData Enemy"
{
	GENERATED_BODY()

private:
	float Life = 0;

public:
	void ApplyDamage(float Damage)
	{
		if (Life <= 0)
			return;
		
		Life -= Damage;
		if (Life <= 0) Death();
	}

	void Death()
	{
		
	}
};

UCLASS(Blueprintable)
class INCREMENTALGAME_5GP_API UIGGameManager : public UWorldSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	TObjectPtr<UIGMathEquations> MaxSpawnCountCurve;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	TObjectPtr<UIGMathEquations> SpawnRateCurve;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Enemy")
	int CurrentMaxEnemyCount;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Enemy")
	float CurrentEnemySpawnRate;

public:
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return true; }
	virtual TStatId GetStatId() const override;

	int GetFursthestEnemy();
	int GetClosestEnemy();
	int GetRandomEnemy();

protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
};

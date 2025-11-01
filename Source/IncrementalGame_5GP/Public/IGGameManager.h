#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "IGEnemyData.h"
#include "MathEquation/IGMathEquations.h"
#include "IGGameManager.generated.h"

class UIGMathEquations;

UCLASS(Blueprintable)
class INCREMENTALGAME_5GP_API UIGGameManager : public UWorldSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UIGMathEquations> MaxSpawnCountCurve;
	
	UPROPERTY()
	TObjectPtr<UIGMathEquations> SpawnRateCurve;
	
	UPROPERTY()
	TObjectPtr<UIGMathEquations> EnemyHealth;
	
	UPROPERTY()
	TObjectPtr<UIGMathEquations> EnemySpeed;
	
	UPROPERTY()
	TObjectPtr<UIGMathEquations> DecreaseZoneCurve;

	float Timer = 0;

	float TimerScale = 0;

	bool bInitialized = false;
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Enemy")
	int CurrentMaxEnemyCount;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Enemy")
	float CurrentEnemySpawnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	TObjectPtr<UInstancedStaticMeshComponent> EnemiesMeshInstances;
	
	TArray<int32> InactiveEnemiesIndices;

	// central tower pos, can be replaced by a ref
	FVector Origin;
	int32 CellSize = 1000; //arbitrary, needs testing, can be modified at runtime depending on the enemies density
	TMap<FIntPoint, TArray<int32>> Grid;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Zone")
	float MinZoneRadius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Zone")
	float MaxZoneRadius;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Zone")
	float CurrentZoneRadius;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Zone")
	float CurrentZoneFrameInvincibility = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Zone")
	float MaxZoneFrameInvincibility = 5;

	uint32 ClosestEnemyIndex;
	uint32 FarthestEnemyIndex;

public:
	TArray<FEnemyData> EnemiesData;
	TArray<int32> ActiveEnemiesIndices;
	TMap<int32, int32> InstanceIdToEnemyIndex;
	
public:
	void InitializeManager(UInstancedStaticMeshComponent* EnemiesMeshInstancesVar, UIGMathEquations* EnemyLifeVar,
		UIGMathEquations* EnemySpeedVar, UIGMathEquations* EnemySpawnVar, UIGMathEquations* EnemyMaxSpawnVar, UIGMathEquations* ZoneVar);
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return true; }
	virtual TStatId GetStatId() const override;

	int32 SpawnEnemy(const FTransform& SpawnTransform);
	void KillEnemy(int EnemyIndex);
	FORCEINLINE FEnemyData& GetEnemy(int32 Index) { return EnemiesData[Index]; }

	uint32 GetFarthestEnemy() const;
	uint32 GetClosestEnemy() const;
	uint32 GetRandomEnemy() const;

	void ChangeZoneSize(float ChangeFactor);

	void ResetManager();
};
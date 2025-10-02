#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "IGEnemyData.h"
#include "IGGameManager.generated.h"

class UIGMathEquations;

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

	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* EnemiesMeshInstances;

	TArray<FEnemyData> EnemiesData;

	TArray<int32> ActiveEnemiesIndices;

	TArray<FVector> EnemiesPositions;

	// central tower pos, can be replaced by a ref
	FVector Origin;
	int32 CellSize = 1000; //arbitrary, needs testing, can be modified at runtime depenting on the enemies density
	TMap<FIntPoint, TArray<int32>> Grid;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Zone")
	TObjectPtr<UIGMathEquations> DecreaseZoneCurve;

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
	
public:
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return true; }
	virtual TStatId GetStatId() const override;

	void InitializeEnemiesMeshInstances(UStaticMesh* Mesh, UMaterialInterface* Material);
	int32 SpawnEnemy(const FTransform& SpawnTransform);
	FORCEINLINE FEnemyData& GetEnemy(int32 Index) { return EnemiesData[Index]; }

	int GetFarthestEnemy();
	int GetClosestEnemy();
	int GetRandomEnemy();

	FIntPoint GetCellCoords(const FVector& Pos) const;
	void InsertIntoGrid(int32 EnemyIndex, const FVector& Pos);
	void RemoveFromGrid(int32 EnemyIndex, const FVector& Pos);

	void ChangeZoneSize(float ChangeFactor);

protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
};
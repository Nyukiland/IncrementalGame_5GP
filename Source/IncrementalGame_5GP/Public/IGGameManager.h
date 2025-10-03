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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	TObjectPtr<UIGMathEquations> EnemyHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	TObjectPtr<UIGMathEquations> EnemySpeed;

	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* EnemiesMeshInstances;

	TArray<FEnemyData> EnemiesData;

	TArray<int32> ActiveEnemiesIndices;

	// central tower pos, can be replaced by a ref
	FVector Origin;
	int32 CellSize = 1000; //arbitrary, needs testing, can be modified at runtime depending on the enemies density
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

	uint32 ClosestEnemyIndex;
	uint32 FarthestEnemyIndex;
	
public:
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return true; }
	virtual TStatId GetStatId() const override;

	void InitializeEnemiesMeshInstances(UStaticMesh* Mesh, UMaterialInterface* Material);
	int32 SpawnEnemy(const FTransform& SpawnTransform);
	FORCEINLINE FEnemyData& GetEnemy(int32 Index) { return EnemiesData[Index]; }

	uint32 GetFarthestEnemy() const;
	uint32 GetClosestEnemy() const;
	uint32 GetRandomEnemy() const;

	void ChangeZoneSize(float ChangeFactor);

protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
};
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
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	TSubclassOf<UIGMathEquations> MaxSpawnCountCurveSubClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	TSubclassOf<UIGMathEquations> SpawnRateCurveSubClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Enemy")
	int CurrentMaxEnemyCount;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Enemy")
	float CurrentEnemySpawnRate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	TSubclassOf<UIGMathEquations> EnemyHealthSubClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	TSubclassOf<UIGMathEquations> EnemySpeedSubClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TObjectPtr<UTexture2D> EnemyVisu;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy")
	TObjectPtr<UStaticMesh> PlaneMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy")
	TObjectPtr<UMaterialInterface> BaseMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	UInstancedStaticMeshComponent* EnemiesMeshInstances;
	
	TArray<int32> InactiveEnemiesIndices;

	// central tower pos, can be replaced by a ref
	FVector Origin;
	int32 CellSize = 1000; //arbitrary, needs testing, can be modified at runtime depending on the enemies density
	TMap<FIntPoint, TArray<int32>> Grid;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Zone")
	TSubclassOf<UIGMathEquations> DecreaseZoneCurveSubClass;

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
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return true; }
	virtual TStatId GetStatId() const override;

	void InitializeEnemiesMeshInstances(UStaticMesh* Mesh, UMaterialInterface* Material);
	int32 SpawnEnemy(const FTransform& SpawnTransform);
	void KillEnemy(int EnemyIndex);
	FORCEINLINE FEnemyData& GetEnemy(int32 Index) { return EnemiesData[Index]; }

	uint32 GetFarthestEnemy() const;
	uint32 GetClosestEnemy() const;
	uint32 GetRandomEnemy() const;

	void ChangeZoneSize(float ChangeFactor);

protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
};
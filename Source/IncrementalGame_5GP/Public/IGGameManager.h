#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "IGEnemyData.h"
#include "MathEquation/IGMathEquations.h"
#include "IGGameManager.generated.h"

class UIGMathEquations;

//Use vector, in case a feedback is required on the position
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDeath, const FVector&, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoose);

UCLASS(Blueprintable)
class INCREMENTALGAME_5GP_API UIGGameManager : public UWorldSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

private:
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	TObjectPtr<UInstancedStaticMeshComponent> EnemiesMeshInstances;
	
	TArray<int32> InactiveEnemiesIndices;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Zone")
	float MinZoneRadius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Zone")
	float MaxZoneRadius;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Zone")
	float CurrentZoneRadius;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Zone")
	int CurrentZoneFrameInvincibility = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Zone")
	int MaxZoneFrameInvincibility = 5;

	uint32 ClosestEnemyIndex;
	uint32 FarthestEnemyIndex;

public:
	UPROPERTY()
	TArray<FEnemyData> EnemiesData;
	UPROPERTY()
	TArray<int32> ActiveEnemiesIndices;
	UPROPERTY()
	TMap<int32, int32> InstanceIdToEnemyIndex;

	UPROPERTY(BlueprintAssignable, Category = "Enemy")
	FOnEnemyDeath OnEnemyDeath;

	UPROPERTY(BlueprintAssignable, Category = "Enemy")
	FOnLoose OnLoose;
	
public:
	void InitializeManager(UInstancedStaticMeshComponent* EnemiesMeshInstancesVar, UIGMathEquations* EnemyLifeVar,
		UIGMathEquations* EnemySpeedVar, UIGMathEquations* EnemySpawnVar, UIGMathEquations* ZoneVar,
		float ZoneMaxRadiusVar, float ZoneMinRadiusVar, int InvincibilityFrameVar);
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
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IGGameManagerInitializer.generated.h"

class UIGMathEquations;

//This script exist due to us not finding how to set the Manager BP to be used
//Therefore we had to set the base var of the manager using an external object
//This is not a proper way to do it, but it was the fastest way
UCLASS(Blueprintable)
class INCREMENTALGAME_5GP_API AIGGameManagerInitializer : public AActor
{
	GENERATED_BODY()
	
public:	
	AIGGameManagerInitializer();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameManagerInitializer")
	TSubclassOf<UIGMathEquations> SpawnRateCurveSubClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameManagerInitializer")
	TSubclassOf<UIGMathEquations> EnemyHealthSubClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameManagerInitializer")
	TSubclassOf<UIGMathEquations> EnemySpeedSubClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameManagerInitializer")
	TObjectPtr<UTexture2D> EnemyVisu;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameManagerInitializer")
	TObjectPtr<UStaticMesh> PlaneMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameManagerInitializer")
	TObjectPtr<UMaterialInterface> BaseMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameManagerInitializer")
	TSubclassOf<UIGMathEquations> DecreaseZoneCurveSubClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameManagerInitializer")
	float ZoneMaxRadius;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameManagerInitializer")
	float ZoneMinRadius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameManagerInitializer")
	int InvincibilityFrame;
	
protected:
	virtual void BeginPlay() override;
};

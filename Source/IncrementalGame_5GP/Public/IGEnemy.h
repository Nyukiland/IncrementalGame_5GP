#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Actor.h"
#include "IGEnemy.generated.h"

class UIGGameManager;
class UIGMathEquations;
class UIGStatus;

UCLASS(Blueprintable)
class INCREMENTALGAME_5GP_API AIGEnemy : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	TObjectPtr<UIGMathEquations> SpeedCurve;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	TObjectPtr<UIGMathEquations> LifeCurve;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Enemy")
	float CurrentLife;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Enemy")
	float CurrentDefenseValue;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Enemy")
	float CurrentSpeed;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Enemy")
	FVector CurrentDirection;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Enemy")
	bool bIsActive;
	
private:
	UPROPERTY()
	TObjectPtr<UIGGameManager> Manager;

public:
	AIGEnemy();

	virtual void BeginPlay() override;
	void InitEnemy(UIGGameManager* GameManager);
	void EnableEnemy(FVector StartPos, FVector Direction, float Time);
	virtual void Tick(float DeltaTime) override;
	void TakeDamage(float Damage);

private:
	void DisableEnemy();
};
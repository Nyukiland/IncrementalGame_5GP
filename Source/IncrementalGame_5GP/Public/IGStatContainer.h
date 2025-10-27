#pragma once

#include "CoreMinimal.h"
#include "MathEquation/IGMathEquations.h"
#include "IGStatContainer.generated.h"

UCLASS(Blueprintable)
class INCREMENTALGAME_5GP_API UIGStatContainer : public UObject
{
	GENERATED_BODY()

private:
	int CurrentUpgradeCount = 0;
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Name = "Name";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UIGMathEquations> UpgradeEquationSubClass;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UIGMathEquations> PriceEquationSubClass;

	UPROPERTY()
	TObjectPtr<UIGMathEquations> UpgradeEquation;
	UPROPERTY()
	TObjectPtr<UIGMathEquations> PriceEquation;
	
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float CurrentValue;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float CurrentPrice;
	
public:
	UFUNCTION(BlueprintCallable)
	void Init();
	
	UFUNCTION(BlueprintCallable)
	bool CheckIfCanUpgrade(int Money);

	UFUNCTION(BlueprintCallable)
	void Upgrade();

	UFUNCTION(BlueprintCallable)
	bool TryUpgrade(int Money);
};
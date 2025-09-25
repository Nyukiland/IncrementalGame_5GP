#pragma once

#include "CoreMinimal.h"
#include "IGMathEquations.h"
#include "IGStatContainer.generated.h"

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class INCREMENTALGAME_5GP_API UIGStatContainer : public UObject
{
	GENERATED_BODY()

private:
	int CurrentUpgradeCount = 0;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Name = "Name";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UIGMathEquations> UpgradeEquation;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UIGMathEquations> PriceEquation;

public:
	float CurrentValue;
	float CurrentPrice;
	
public:
	UFUNCTION(BlueprintCallable)
	void Init();
	
	UFUNCTION(BlueprintCallable)
	bool CheckIfCanUpgrade(float Money);

	UFUNCTION(BlueprintCallable)
	void Upgrade();

	UFUNCTION(BlueprintCallable)
	bool TryUpgrade(float Money);
};
#pragma once

#include "CoreMinimal.h"
#include "IGMathEquations.generated.h"

UCLASS(Abstract, Blueprintable)
class INCREMENTALGAME_5GP_API UIGMathEquations : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Math")
	float GetValue(int T);
	virtual float GetValue_Implementation(int T);
};
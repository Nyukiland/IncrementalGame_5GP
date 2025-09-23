#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IGMathEquations.generated.h"

UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class INCREMENTALGAME_5GP_API UIGMathEquations : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Math")
	float GetValue(int T);
	virtual float GetValue_Implementation(int T);
};
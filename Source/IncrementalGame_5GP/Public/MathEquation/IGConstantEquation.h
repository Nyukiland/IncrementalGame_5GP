#pragma once

#include "CoreMinimal.h"
#include "IGMathEquations.h"
#include "IGConstantEquation.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGConstantEquation : public UIGMathEquations
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Math")
	float Value = 1;
	
public:
	virtual float GetValue_Implementation(int T) override;
};
#pragma once

#include "CoreMinimal.h"
#include "IGMathEquations.h"
#include "IGLinearEquation.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGLinearEquation : public UIGMathEquations
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Math")
	float A = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Math")
	float B = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Math")
	float C = 0;
	
public:
	virtual float GetValue_Implementation(int T) override;
};

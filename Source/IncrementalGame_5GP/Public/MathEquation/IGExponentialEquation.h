#pragma once

#include "CoreMinimal.h"
#include "IGMathEquations.h"
#include "IGExponentialEquation.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGExponentialEquation : public UIGMathEquations
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Math")
	FName Equation = "Y = A * (FMath::Pow(A, ((B* X) + C))) + D";
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Math")
	float A = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Math")
	float B = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Math")
	float C = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Math")
	float D = 0;
	
public:
	virtual float GetValue_Implementation(int T) override;
};
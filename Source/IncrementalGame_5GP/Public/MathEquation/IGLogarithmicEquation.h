#pragma once

#include "CoreMinimal.h"
#include "IGMathEquations.h"
#include "IGLogarithmicEquation.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGLogarithmicEquation : public UIGMathEquations
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Math")
	FName Equation = "Y = (A * FMath::LogX(B,(C * X) + D)) + E";
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Math")
	float A = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Math")
	float B = 2;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Math")
	float C = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Math")
	float D = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Math")
	float E = 0;
	
public:
	virtual float GetValue_Implementation(int T) override; 
};
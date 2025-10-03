#pragma once

#include "CoreMinimal.h"
#include "IGMathHelper.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGMathHelper : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Math Helper")
	static FVector GetRandomPointInCircle();
};
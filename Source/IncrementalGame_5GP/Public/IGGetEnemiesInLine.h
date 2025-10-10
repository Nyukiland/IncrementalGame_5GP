#pragma once

#include "CoreMinimal.h"
#include "IGCapacityEffect.h"
#include "IGGetEnemiesInLine.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGGetEnemiesInLine : public UIGCapacityEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemiesInLine")
	float ToleranceRadius = 10;
	
public:
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData) override;
};

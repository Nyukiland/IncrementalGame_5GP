#pragma once

#include "CoreMinimal.h"
#include "IGCapacityEffect.h"
#include "IGGetFurthestEnemyEffect.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGGetFurthestEnemyEffect : public UIGCapacityEffect
{
	GENERATED_BODY()

public:
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData) override;
};

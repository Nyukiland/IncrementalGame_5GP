#pragma once

#include "CoreMinimal.h"
#include "IGCapacityEffect.h"
#include "IGGetRandomEnemyEffect.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGGetRandomEnemyEffect : public UIGCapacityEffect
{
	GENERATED_BODY()

public:
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData) override;
};

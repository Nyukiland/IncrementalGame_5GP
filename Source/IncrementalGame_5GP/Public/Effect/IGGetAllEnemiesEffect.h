#pragma once

#include "CoreMinimal.h"
#include "Effect/IGCapacityEffect.h"
#include "IGGetAllEnemiesEffect.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGGetAllEnemiesEffect : public UIGCapacityEffect
{
	GENERATED_BODY()

public:
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData) override;
};

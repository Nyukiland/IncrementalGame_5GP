#pragma once

#include "CoreMinimal.h"
#include "IGCapacityEffect.h"
#include "IGDealDamageEffect.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGDealDamageEffect : public UIGCapacityEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DealDamageEffect")
	TObjectPtr<UIGStatContainer> DamageStat;
	
public:
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData) override;
};

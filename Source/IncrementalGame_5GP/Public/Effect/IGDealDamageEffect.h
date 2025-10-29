#pragma once

#include "CoreMinimal.h"
#include "IGCapacityEffect.h"
#include "IGDealDamageEffect.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGDealDamageEffect : public UIGCapacityEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DealDamageEffect")
	TSubclassOf<UIGStatContainer> DamageStatSubClass;
	
public:
	UPROPERTY()
	TObjectPtr<UIGStatContainer> DamageStat;
	
public:
	virtual void InitEffect_Implementation() override;
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData) override;
	virtual TArray<UIGStatContainer*> GetStats_Implementation() override;
	virtual void ResetEffectCompletly_Implementation() override;
};

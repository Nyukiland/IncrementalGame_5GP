#pragma once

#include "CoreMinimal.h"
#include "IGCapacityEffect.h"
#include "IGStatus.h"
#include "IGGiveStatusEffect.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGGiveStatusEffect : public UIGCapacityEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	FStatus StatusToGive;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	TObjectPtr<UIGStatContainer> DamageStat;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	TObjectPtr<UIGStatContainer> SlowEffectStat;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	TObjectPtr<UIGStatContainer> DurationStat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	TObjectPtr<UIGStatContainer> TimeBetweenShotsStat;

public:
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData) override;
	virtual TArray<UIGStatContainer*> GetStats_Implementation() override;
};

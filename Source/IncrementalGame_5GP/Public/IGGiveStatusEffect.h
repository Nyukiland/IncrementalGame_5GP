#pragma once

#include "CoreMinimal.h"
#include "IGCapacityEffect.h"
#include "IGStatus.h"
#include "IGGiveStatusEffect.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGGiveStatusEffect : public UIGCapacityEffect
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	FStatus StatusToGive;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	TSubclassOf<UIGStatContainer> DamageStatSubClass;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	TSubclassOf<UIGStatContainer> SlowEffectStatSubClass;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	TSubclassOf<UIGStatContainer> DurationStatSubClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	TSubclassOf<UIGStatContainer> TimeBetweenShotsStatSubClass;

public:
	UPROPERTY()
	TObjectPtr<UIGStatContainer> DamageStat;
	UPROPERTY()
	TObjectPtr<UIGStatContainer> SlowEffectStat;
	UPROPERTY()
	TObjectPtr<UIGStatContainer> DurationStat;
	UPROPERTY()
	TObjectPtr<UIGStatContainer> TimeBetweenShotsStat;

public:
	virtual void InitEffect_Implementation() override;
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData) override;
	virtual TArray<UIGStatContainer*> GetStats_Implementation() override;
};

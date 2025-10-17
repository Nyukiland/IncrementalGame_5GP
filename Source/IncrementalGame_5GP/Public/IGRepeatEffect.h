#pragma once

#include "CoreMinimal.h"
#include "IGCapacityEffect.h"
#include "IGRepeatEffect.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGRepeatEffect : public UIGCapacityEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RepeatEffect")
	TSubclassOf<UIGStatContainer> RepeatStatSubClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RepeatEffect")
	TArray<TSubclassOf<UIGCapacityEffect>> EffectsSubClass;

	int LoopIndex;
	
public:
	UPROPERTY()
	TObjectPtr<UIGStatContainer> RepeatStat;
	
	UPROPERTY()
	TArray<TObjectPtr<UIGCapacityEffect>> Effects;

public:
	virtual void InitEffect_Implementation() override;
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData) override;
	virtual TArray<UIGStatContainer*> GetStats_Implementation() override;

private:
	bool ExecuteEffect(FCapacityData& CapacityData);
};

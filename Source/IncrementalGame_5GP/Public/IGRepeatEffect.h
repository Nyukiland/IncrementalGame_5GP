#pragma once

#include "CoreMinimal.h"
#include "IGCapacityEffect.h"
#include "IGRepeatEffect.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGRepeatEffect : public UIGCapacityEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RepeatEffect")
	TObjectPtr<UIGStatContainer> RepeatStat;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RepeatEffect")
	TArray<TObjectPtr<UIGCapacityEffect>> Effects;

public:
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData) override;
	virtual TArray<UIGStatContainer*> GetStats_Implementation() override;

private:
	bool ExecuteEffect(FCapacityData& CapacityData);
};

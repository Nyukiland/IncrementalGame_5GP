#pragma once

#include "CoreMinimal.h"
#include "Effect/IGCapacityEffect.h"
#include "IGGetClosestEnemyInAreaEffect.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGGetClosestEnemyInAreaEffect : public UIGCapacityEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Get Closest Enemy In Area")
	TSubclassOf<UIGStatContainer> AreaStatSubClass;

private:
	UPROPERTY()
	TObjectPtr<UIGStatContainer> Area;

public:
	virtual void InitEffect_Implementation() override;
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData) override;
	virtual TArray<UIGStatContainer*> GetStats_Implementation() override;
	virtual void ResetEffectCompletly_Implementation() override;
};

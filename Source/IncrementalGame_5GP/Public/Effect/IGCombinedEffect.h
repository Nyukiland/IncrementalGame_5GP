#pragma once

#include "CoreMinimal.h"
#include "Effect/IGCapacityEffect.h"
#include "IGCombinedEffect.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGCombinedEffect : public UIGCapacityEffect
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<TObjectPtr<UIGCapacityEffect>> Effects;

	UPROPERTY()
	FCapacityData LocalCapacityData;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CombinedEffect")
	TArray<TSubclassOf<UIGCapacityEffect>> EffectSubClasses;
	
public:
	virtual void InitEffect_Implementation() override;
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData) override;
	virtual TArray<UIGStatContainer*> GetStats_Implementation() override;
	virtual void ResetEffectCompletly_Implementation() override;
};

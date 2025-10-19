#pragma once

#include "CoreMinimal.h"
#include "IGCapacityEffect.h"
#include "IGHealEffect.generated.h"

class UIGStatContainer;
class UIGGameManager;

UCLASS()
class INCREMENTALGAME_5GP_API UIGHealEffect : public UIGCapacityEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
	TSubclassOf<UIGStatContainer> HealStatSubClass;

public:
	UPROPERTY()
	TObjectPtr<UIGStatContainer> HealStat;

private:
	UPROPERTY()
	UIGGameManager* Manager;
	
public:
	virtual void InitEffect_Implementation() override;
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData) override;
	virtual TArray<UIGStatContainer*> GetStats_Implementation() override;
};

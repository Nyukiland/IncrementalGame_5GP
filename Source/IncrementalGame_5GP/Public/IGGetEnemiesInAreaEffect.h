#pragma once

#include "CoreMinimal.h"
#include "IGCapacityEffect.h"
#include "IGGetEnemiesInAreaEffect.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGGetEnemiesInAreaEffect : public UIGCapacityEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Area Effect")
	TSubclassOf<UIGStatContainer> AreaSizeSubClass;

public:
	UPROPERTY()
	TObjectPtr<UIGStatContainer> AreaSize;
	
public:
	virtual void InitEffect_Implementation() override;
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData) override;
	virtual TArray<UIGStatContainer*> GetStats_Implementation() override;
};

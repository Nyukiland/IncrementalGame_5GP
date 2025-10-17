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

public:
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData) override;
};

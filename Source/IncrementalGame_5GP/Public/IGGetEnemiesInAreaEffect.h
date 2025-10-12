#pragma once

#include "CoreMinimal.h"
#include "IGCapacityEffect.h"
#include "IGGetEnemiesInAreaEffect.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGGetEnemiesInAreaEffect : public UIGCapacityEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Area Effect")\
	TObjectPtr<UIGStatContainer> AreaSize;
	
public:
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData) override;
};

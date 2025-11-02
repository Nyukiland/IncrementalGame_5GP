#pragma once

#include "CoreMinimal.h"
#include "Effect/IGCapacityEffect.h"
#include "IGStandardProjectileEffect.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGStandardProjectileEffect : public UIGCapacityEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FColor Color;
	
public:
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData) override;
};

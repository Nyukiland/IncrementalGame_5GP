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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float ProjectileTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float ProjectileSize;
	
public:
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData) override;
};

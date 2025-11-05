#pragma once

#include "CoreMinimal.h"
#include "Effect/IGCapacityEffect.h"
#include "IGProjectileLineEffect.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGProjectileLineEffect : public UIGCapacityEffect
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float ProjectileSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float ProjectileTime;
	
public:
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData) override;
};

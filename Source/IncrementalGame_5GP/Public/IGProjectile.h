#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IGProjectile.generated.h"

class UIGStatus;
class UIGCapacityEffect;

UCLASS()
class INCREMENTALGAME_5GP_API AIGProjectile : public AActor
{
	GENERATED_BODY()

public:
	AIGProjectile();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
	TArray<TObjectPtr<UIGCapacityEffect>> Effects;

private:
	bool CheckValidity();
	void DoEffects();
};

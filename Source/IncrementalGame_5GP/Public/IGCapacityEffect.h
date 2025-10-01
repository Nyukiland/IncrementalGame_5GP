#pragma once

#include "CoreMinimal.h"
#include "IGEnemyData.h"
#include "IGPlayer.h"
#include "IGCapacityEffect.generated.h"

class UIGStatContainer;

UCLASS(Abstract, Blueprintable)
class INCREMENTALGAME_5GP_API UIGCapacityEffect : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Capacity|Effect")
	void ApplyEffect(AIGPlayer* Player, FVector Target);
	virtual void ApplyEffect_Implementation(AIGPlayer* Player, FVector Target);

	UFUNCTION(BlueprintNativeEvent, Category = "Capacity|Effect")
	void ApplyEffectToEnemy(AIGPlayer* Player, FEnemyData& Target);
	virtual void ApplyEffectToEnemy_Implementation(AIGPlayer* Player, FEnemyData& Target);

	UFUNCTION(BlueprintNativeEvent, Category = "Capacity|Effect")
	TArray<UIGStatContainer*> GetStats();
	virtual TArray<UIGStatContainer*> GetStats_Implementation();
};
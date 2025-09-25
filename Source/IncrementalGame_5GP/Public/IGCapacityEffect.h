#pragma once

#include "CoreMinimal.h"
#include "IGCapacityEffect.generated.h"

class UIGStatContainer;

UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class INCREMENTALGAME_5GP_API UIGCapacityEffect : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Capacity|Effect")
	void ApplyEffect(AActor* Source, AActor* Target);
	virtual void ApplyEffect_Implementation(AActor* Source, AActor* Target);

	UFUNCTION(BlueprintNativeEvent, Category = "Capacity|Effect")
	TArray<UIGStatContainer*> GetStats();
	virtual TArray<UIGStatContainer*> GetStats_Implementation();
};
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IGCapacityEffect.generated.h"

//class UStatContainer;

UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class INCREMENTALGAME_5GP_API UIGCapacityEffect : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Capacity|Effect")
	void ApplyEffect(AActor* Source, AActor* Target);
	virtual void ApplyEffect_Implementation(AActor* Source, AActor* Target);

	// UFUNCTION(BlueprintNativeEvent, Category = "Capacity|Effect")
	// TArray<UIGStatContainer*> GetStats();
	// virtual TArray<UStatContainer*> GetStats_Implementation();
};
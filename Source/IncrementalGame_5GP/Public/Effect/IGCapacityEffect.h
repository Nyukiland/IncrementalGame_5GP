#pragma once

#include "CoreMinimal.h"
#include "IGCapacityData.h"
#include "IGCapacityEffect.generated.h"

class UIGStatContainer;

UCLASS(Abstract, Blueprintable)
class INCREMENTALGAME_5GP_API UIGCapacityEffect : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capacity|Effect")
	float Duration = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capacity|Effect")
	float Timer = -1;
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Capacity|Effect")
	void InitEffect();
	virtual void InitEffect_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, Category = "Capacity|Effect")
	void ApplyEffect(FCapacityData& CapacityData);
	virtual void ApplyEffect_Implementation(FCapacityData& CapacityData);

	UFUNCTION(BlueprintNativeEvent, Category = "Capacity|Effect")
	TArray<UIGStatContainer*> GetStats();
	virtual TArray<UIGStatContainer*> GetStats_Implementation();
};
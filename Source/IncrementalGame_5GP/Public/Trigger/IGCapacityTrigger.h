#pragma once

#include "CoreMinimal.h"
#include "IGCapacityTrigger.generated.h"

class UIGStatContainer;

UCLASS(Abstract, Blueprintable)
class INCREMENTALGAME_5GP_API UIGCapacityTrigger : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capacity|Trigger")
	bool bTriggerReady = false;

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Capacity|Trigger")
	void InitTrigger();
	virtual void InitTrigger_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, Category = "Capacity|Trigger")
	void TickTrigger(float DeltaTime);
	virtual void TickTrigger_Implementation(float DeltaTime);
	
	UFUNCTION(BlueprintNativeEvent, Category = "Capacity|Trigger")
	void ResetTrigger();
	virtual void ResetTrigger_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Capacity|Trigger")
	TArray<UIGStatContainer*> GetStats();
	virtual TArray<UIGStatContainer*> GetStats_Implementation();
};
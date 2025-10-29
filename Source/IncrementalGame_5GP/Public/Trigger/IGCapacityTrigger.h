#pragma once

#include "CoreMinimal.h"
#include "IGCapacityTrigger.generated.h"

class AIGPlayer;
class UIGStatContainer;

UCLASS(Abstract, Blueprintable)
class INCREMENTALGAME_5GP_API UIGCapacityTrigger : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capacity|Trigger")
	bool bTriggerReady = false;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Capacity|Trigger")
	void InitTrigger(AIGPlayer* Player);
	virtual void InitTrigger_Implementation(AIGPlayer* Player);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Capacity|Trigger")
	void TickTrigger(float DeltaTime);
	virtual void TickTrigger_Implementation(float DeltaTime);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Capacity|Trigger")
	void ResetTrigger();
	virtual void ResetTrigger_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Capacity|Trigger")
	TArray<UIGStatContainer*> GetStats();
	virtual TArray<UIGStatContainer*> GetStats_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Capacity|Trigger")
	void ResetTriggerCompletly();
	virtual void ResetTriggerCompletly_Implementation();
};
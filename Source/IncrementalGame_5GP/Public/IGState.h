#pragma once

#include "CoreMinimal.h"
#include "IGState.generated.h"

class AGameController;
class UStateComponent;

UCLASS(Abstract, Blueprintable)
class INCREMENTALGAME_5GP_API UIGState : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	AGameController* Owner;

public:
	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnEnter(AGameController* GameController);
	virtual void OnEnter_Implementation(AGameController* GameController);
	
	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnExit();
	virtual void OnExit_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnTick(float DeltaTime);
	virtual void OnTick_Implementation(float DeltaTime);
};
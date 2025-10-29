#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IGStateComponent.generated.h"

class AIGPlayer;

UCLASS(Abstract, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INCREMENTALGAME_5GP_API UIGStateComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<AIGPlayer> Owner;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StateComponent")
	bool bActive;

public:	
	UIGStateComponent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StateComponent")
	void InitStateComponent(AIGPlayer* Controller);
	virtual void InitStateComponent_Implementation(AIGPlayer* Controller);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StateComponent")
	void EnableStateComponent();
	virtual void EnableStateComponent_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StateComponent")
	void DisableStateComponent();
	virtual void DisableStateComponent_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StateComponent")
	void TickStateComponent(float DeltaTime);
	virtual void TickStateComponent_Implementation(float DeltaTime);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Capacity")
	void ResetComponent();
	virtual void ResetComponent_Implementation();
};
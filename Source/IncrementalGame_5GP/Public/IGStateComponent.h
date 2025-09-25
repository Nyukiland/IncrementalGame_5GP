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
	TObjectPtr<AIGPlayer> Owner;

public:	
	UIGStateComponent();

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void InitStateComponent(AIGPlayer* Controller);
	virtual void InitStateComponent_Implementation(AIGPlayer* Controller);

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void EnableStateComponent();
	virtual void EnableStateComponent_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void DisableStateComponent();
	virtual void DisableStateComponent_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void TickStateComponent(float DeltaTime);
	virtual void TickStateComponent_Implementation(float DeltaTime);
};
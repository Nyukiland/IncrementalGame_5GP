#pragma once

#include "CoreMinimal.h"
#include "IGStateComponent.h"
#include "IGCapacityComponent.generated.h"

class UIGCapacityTrigger;
class UIGCapacityEffect;

UCLASS()
class INCREMENTALGAME_5GP_API UIGCapacityComponent : public UIGStateComponent
{
	GENERATED_BODY()
	
private:
	bool CheckValidity();

	void ExecuteEffect();

	bool CheckTriggers();

public:
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = "Capacity")
	TArray<UIGCapacityTrigger*> Triggers;

	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = "Capacity")
	TArray<UIGCapacityEffect*> Effects;

	virtual void EnableStateComponent_Implementation() override;

	virtual void DisableStateComponent_Implementation() override;

	virtual void TickStateComponent_Implementation(float DeltaTime) override;
};
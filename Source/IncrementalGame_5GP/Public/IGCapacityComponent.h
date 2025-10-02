#pragma once

#include "CoreMinimal.h"
#include "IGCapacityData.h"
#include "IGStateComponent.h"
#include "IGCapacityComponent.generated.h"

class UIGGameManager;
struct FEnemyData;
class UIGCapacityTrigger;
class UIGCapacityEffect;

UCLASS()
class INCREMENTALGAME_5GP_API UIGCapacityComponent : public UIGStateComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capacity")
	FCapacityData CapacityData;

private:
	bool CheckValidity();

	void ExecuteEffect();

	bool CheckTriggers();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capacity")
	TArray<TObjectPtr<UIGCapacityTrigger>> Triggers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capacity")
	TArray<TObjectPtr<UIGCapacityEffect>> Effects;

	virtual void InitStateComponent_Implementation(AIGPlayer* Controller) override;
	
	virtual void EnableStateComponent_Implementation() override;

	virtual void DisableStateComponent_Implementation() override;

	virtual void TickStateComponent_Implementation(float DeltaTime) override;
};
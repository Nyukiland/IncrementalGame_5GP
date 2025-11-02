#pragma once

#include "CoreMinimal.h"
#include "IGCapacityData.h"
#include "IGStateComponent.h"
#include "IGCapacityComponent.generated.h"

class UIGStatContainer;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capacity")
	TArray<TSubclassOf<UIGCapacityTrigger>> TriggersSubClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capacity")
	TArray<TSubclassOf<UIGCapacityEffect>> EffectsSubClass;
	
private:
	bool CheckValidity();

	bool ExecuteEffect(float DeltaTime);

	bool CheckTriggers(float DeltaTime);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capacity")
	TObjectPtr<UTexture2D> SpriteVisu;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capacity")
	FName Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capacity")
	float Price;

	UPROPERTY()
	TArray<TObjectPtr<UIGCapacityTrigger>> Triggers;

	UPROPERTY()
	TArray<TObjectPtr<UIGCapacityEffect>> Effects;

	virtual void InitStateComponent_Implementation(AIGPlayer* Controller) override;
	
	virtual void EnableStateComponent_Implementation() override;

	virtual void DisableStateComponent_Implementation() override;

	virtual void TickStateComponent_Implementation(float DeltaTime) override;

	virtual void ResetComponent_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Capacity")
	TArray<UIGStatContainer*> GetStats();
	virtual TArray<UIGStatContainer*> GetStats_Implementation();
};
#pragma once

#include "CoreMinimal.h"
#include "IGStateComponent.h"
#include "IGMoneyComponent.generated.h"

class UIGStatContainer;

UCLASS()
class INCREMENTALGAME_5GP_API UIGMoneyComponent : public UIGStateComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UIGStatContainer> MoneyPerKill;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoneyComponent")
	TSubclassOf<UIGStatContainer> MoneyPerKillSubClass;
	
private:
	int Money;

public:
	virtual void InitStateComponent_Implementation(AIGPlayer* Controller) override;
	virtual void ResetComponent_Implementation() override;
	
	UFUNCTION(BlueprintCallable, Category = "MoneyComponent")
	int CurrentMoney();
	UFUNCTION(BlueprintCallable, Category = "MoneyComponent")
	void GiveMoney(int NewAmount);
	UFUNCTION(BlueprintCallable, Category = "MoneyComponent")
	void RemoveMoney(int DelAmount);
	UFUNCTION(BlueprintCallable, Category = "MoneyComponent")
	bool HasEnoughMoney(int Amount);
	UFUNCTION(BlueprintCallable, Category = "MoneyComponent")
	bool TryBuy(int Amount);

private:
	UFUNCTION()
	void OnEnemyDeath(const FVector& DeathTransform);
};

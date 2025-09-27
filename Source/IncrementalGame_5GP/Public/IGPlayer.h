#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "IGPlayer.generated.h"

class UIGState;
class UIGStateComponent;

UCLASS()
class INCREMENTALGAME_5GP_API AIGPlayer : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "State")
	TSubclassOf<UIGState> DefaultState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "State")
	TArray<TSubclassOf<UIGStateComponent>> DefaultActiveComponent;

private:
	UPROPERTY()
	TArray<TObjectPtr<UIGStateComponent>> StateComponents;
	int ActiveComponentCount = 0;
	UPROPERTY()
	TObjectPtr<UIGState> CurrentState;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "State")
	UIGStateComponent* GetStateComponentByClass(TSubclassOf<UIGStateComponent> ComponentClass);
	UIGStateComponent* GetStateComponentByClass(TSubclassOf<UIGStateComponent> ComponentClass, int& Index);

	UFUNCTION(BlueprintCallable, Category = "State")
	void ActivateStateComponent(TSubclassOf<UIGStateComponent> ComponentClass);
	void ActivateStateComponent(UIGStateComponent* Comp, int Index);

	UFUNCTION(BlueprintCallable, Category = "State")
	void DeactivateStateComponent(TSubclassOf<UIGStateComponent> ComponentClass);
	void DeactivateStateComponent(UIGStateComponent* Comp, int Index);

	UFUNCTION(BlueprintCallable, Category = "State")
	void ChangeState(TSubclassOf<UIGState> StateClass);
};

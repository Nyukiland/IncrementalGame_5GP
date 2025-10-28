#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "IGPlayer.generated.h"

class UIGState;
class UIGStateComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventCalled, const FString&, Value);

UCLASS()
class INCREMENTALGAME_5GP_API AIGPlayer : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
	TSubclassOf<UIGState> DefaultState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
	TArray<TSubclassOf<UIGStateComponent>> DefaultActiveComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	TArray<TObjectPtr<UIGStateComponent>> StateComponents;

	UPROPERTY(BlueprintAssignable, Category = "Player")
	FOnEventCalled OnEventCalled;
	
private:
	int ActiveComponentCount = 0;
	UPROPERTY()
	TObjectPtr<UIGState> CurrentState;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Player")
	UIGStateComponent* GetStateComponentByClass(TSubclassOf<UIGStateComponent> ComponentClass);
	UIGStateComponent* GetStateComponentByClass(TSubclassOf<UIGStateComponent> ComponentClass, int& Index);

	UFUNCTION(BlueprintCallable, Category = "Player")
	void ActivateStateComponent(TSubclassOf<UIGStateComponent> ComponentClass);
	void ActivateStateComponent(UIGStateComponent* Comp, int Index);

	UFUNCTION(BlueprintCallable, Category = "Player")
	void DeactivateStateComponent(TSubclassOf<UIGStateComponent> ComponentClass);
	void DeactivateStateComponent(UIGStateComponent* Comp, int Index);

	UFUNCTION(BlueprintCallable, Category = "Player")
	void ChangeState(TSubclassOf<UIGState> StateClass);

	UFUNCTION(BlueprintCallable, Category = "Player")
	void CallOnEvent(const FString& Value);
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MathEquation/IGMathEquations.h"
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
	TArray<TSubclassOf<UIGStateComponent>> DefaultActiveComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	TArray<TObjectPtr<UIGStateComponent>> StateComponents;

	UPROPERTY(BlueprintAssignable, Category = "Player")
	FOnEventCalled OnEventCalled;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	int CurrentPrestige;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	int KillCount;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	float PrestigeKillNeeded;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
	TSubclassOf<UIGMathEquations> PrestigeKillNeededMathSubClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
	TSubclassOf<UIGMathEquations> SlotCountMathSubClass;
	
	int ActiveComponentCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	TObjectPtr<UIGMathEquations> PrestigeKillNeededMath;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	TObjectPtr<UIGMathEquations> SlotCountMath;

	UPROPERTY()
	int MaxSlotCount;
	
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
	void CallOnEvent(FString Value);

	UFUNCTION(BlueprintCallable, Category = "Player")
	bool CheckPrestigeUpgrade(int PrestigeKillCount);

	UFUNCTION(BlueprintCallable, Category = "Player")
	bool CheckSlotFull();
	
	UFUNCTION(BlueprintCallable, Category = "Player")
	void UpgradePrestige();
	
	UFUNCTION(BlueprintCallable, Category = "Player")
	void ResetGame();

	UFUNCTION(BlueprintCallable, Category = "Player")
	float GetCurrentPrestigeNeeded();

private:
	UFUNCTION()
	void IncreaseKillCount(const FVector& Value);
};

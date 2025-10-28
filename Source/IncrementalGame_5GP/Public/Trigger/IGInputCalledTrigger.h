#pragma once

#include "CoreMinimal.h"
#include "Trigger/IGCapacityTrigger.h"
#include "IGInputCalledTrigger.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGInputCalledTrigger : public UIGCapacityTrigger
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	float ToleranceValidity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	FString EventChecker = "InputTrigger";

private:
	float ToleranceTimer = 0;

public:
	virtual void InitTrigger_Implementation(AIGPlayer* Player) override;
	virtual void TickTrigger_Implementation(float DeltaTime) override;
	virtual void ResetTrigger_Implementation() override;

private:
	UFUNCTION()
	void OnEventReceived(const FString& Value);
};

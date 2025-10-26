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

private:
	float ToleranceTimer = 0;

public:
	virtual void TickTrigger_Implementation(float DeltaTime) override;
	virtual void ResetTrigger_Implementation() override;
};

#pragma once

#include "CoreMinimal.h"
#include "IGCapacityTrigger.h"
#include "IGTimerTrigger.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGTimerTrigger : public UIGCapacityTrigger
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	TSubclassOf<UIGStatContainer> MaxTimerSubClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger")
	float Timer = 0;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UIGStatContainer> MaxTimer;
	
public:
	virtual void InitTrigger_Implementation(AIGPlayer* Player) override;
	virtual void TickTrigger_Implementation(float DeltaTime) override;
	virtual void ResetTrigger_Implementation() override;
	virtual TArray<UIGStatContainer*> GetStats_Implementation() override;
	virtual void ResetTriggerCompletly_Implementation() override;
};

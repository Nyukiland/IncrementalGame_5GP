#pragma once

#include "CoreMinimal.h"
#include "IGCapacityTrigger.h"
#include "IGConstantValidTrigger.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API UIGConstantValidTrigger : public UIGCapacityTrigger
{
	GENERATED_BODY()
	
public:
	virtual void TickTrigger_Implementation(float DeltaTime) override;
	virtual void ResetTrigger_Implementation() override;
};

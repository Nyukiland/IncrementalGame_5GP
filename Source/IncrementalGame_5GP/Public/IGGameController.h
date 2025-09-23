#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "IGGameController.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API AIGGameController : public APawn
{
	GENERATED_BODY()

public:
	AIGGameController();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
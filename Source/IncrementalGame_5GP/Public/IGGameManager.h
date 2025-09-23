#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IGGameManager.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API AIGGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AIGGameManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
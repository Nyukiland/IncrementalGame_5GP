#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IGEnemy.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API AIGEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	AIGEnemy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
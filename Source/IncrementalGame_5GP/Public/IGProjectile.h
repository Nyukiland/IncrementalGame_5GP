#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IGProjectile.generated.h"

UCLASS()
class INCREMENTALGAME_5GP_API AIGProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AIGProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
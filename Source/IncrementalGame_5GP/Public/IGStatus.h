#pragma once

#include "CoreMinimal.h"
#include "IGStatus.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FStatus
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	FName Name;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	bool bOneShot = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	bool bCanStack = false;

private:
	float Timer = 0;
		
	float Damage;
	float SlowEffect;
	float Duration;
	float TimeBetweenShots;

public:
	void InitStatus(float DamageValue, float SlowEffectValue, float DurationValue, float TimeBetweenShotsValue);
	bool UpdateStatus(float DeltaTime, float& DamageOut, float& SlowFactorOut);
};
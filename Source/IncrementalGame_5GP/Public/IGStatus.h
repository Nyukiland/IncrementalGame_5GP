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
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	float Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	float DamageMultiplier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	float SlowEffect;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	float Duration;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	float TimeBetweenShots;
	
private:
	float Timer = 0;
		

public:
	void InitStatus();
	bool UpdateStatus(float DeltaTime, float& DamageOut, float& SlowFactorOut);
};
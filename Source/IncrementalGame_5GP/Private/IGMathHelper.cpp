#include "IGMathHelper.h"

FVector UIGMathHelper::GetRandomPointInCircle()
{
	float RandomX = FMath::RandRange(-1, 1);
	float RandomY = FMath::RandRange(-1, 1);
	return FVector(RandomX, RandomY, 0).GetSafeNormal(); 
}
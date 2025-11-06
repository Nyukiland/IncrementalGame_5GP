#include "IGMathHelper.h"

FVector UIGMathHelper::GetRandomPointInCircle()
{
	float Angle = FMath::RandRange(0.0f, 2 * PI);
	return FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0);
}
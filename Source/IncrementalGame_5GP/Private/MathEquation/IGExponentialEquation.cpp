#include "MathEquation/IGExponentialEquation.h"

float UIGExponentialEquation::GetValue_Implementation(int T)
{
	return A * (FMath::Pow(B, ((C* T) + D))) + E;
}

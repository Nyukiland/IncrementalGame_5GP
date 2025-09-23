#include "IGExponentialEquation.h"

float UIGExponentialEquation::GetValue_Implementation(int T)
{
	return A * (FMath::Pow(A, ((B* T) + C))) + D;
}

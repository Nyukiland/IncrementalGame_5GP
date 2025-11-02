#include "MathEquation/IGLogarithmicEquation.h"

float UIGLogarithmicEquation::GetValue_Implementation(int T)
{
	return (A * FMath::LogX(B,(C * T + 1) + D)) + E;
}

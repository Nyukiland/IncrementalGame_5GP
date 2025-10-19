#include "MathEquation/IGLinearEquation.h"

float UIGLinearEquation::GetValue_Implementation(int T)
{
	return (A * (T + B)) + C;
}

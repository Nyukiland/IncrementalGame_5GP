#include "IGCapacityData.h"

void FCapacityData::ResetData()
{
	CurrentAimPositon = FVector::ZeroVector;
	PreviousAimPosition = FVector::ZeroVector;

	EnemiesIndex.Empty();
}

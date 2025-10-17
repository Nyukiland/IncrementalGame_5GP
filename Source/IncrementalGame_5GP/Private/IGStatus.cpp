#include "IGStatus.h"

void FStatus::InitStatus()
{
	Timer = 0;
}

bool FStatus::UpdateStatus(float DeltaTime, float& DamageOut, float& SlowFactorOut)
{
	if (bOneShot || Duration <= 0 || Timer >= Duration)
	{
		DamageOut += Damage;
		SlowFactorOut += SlowEffect;
		return true;
	}

	Timer += DeltaTime;
	
	if (Timer > TimeBetweenShots)
	{
		Timer = 0;
		DamageOut += Damage;
		SlowFactorOut += SlowEffect;

		Duration -= TimeBetweenShots;
	}

	return false;
}
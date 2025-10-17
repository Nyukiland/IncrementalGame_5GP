#include "IGEnemyData.h"

void FEnemyData::ApplyDamage(float Damage)
{
	if (Health <= 0)
		return;

	for (FStatus Status : Statuses)
	{
		Damage *= Status.DamageMultiplier;
	}
	
	Health -= Damage;
	if (Health <= 0) Death();
}

void FEnemyData::Death()
{
}

void FEnemyData::SetActive(bool bNewActive)
{
	// It might be better not to make that condition, it could be a problem at init
	// if (bIsActive_Internal == bNewActive)
	//		return;

	if (!ActiveEnemiesIndices)
		return;

	if (!EnemiesData->IsValidIndex(InstanceId))
		return;

	bIsActive_Internal = bNewActive;

	if (bIsActive_Internal)
	{
		if (!ActiveEnemiesIndices->Contains(InstanceId))
			ActiveEnemiesIndices->Add(InstanceId);
		if (InactiveEnemiesIndices->Contains(InstanceId))
			InactiveEnemiesIndices->Remove(InstanceId);
	}
	else if (ActiveEnemiesIndices->Contains(InstanceId))
		ActiveEnemiesIndices->Remove(InstanceId);
	if (!InactiveEnemiesIndices->Contains(InstanceId))
		InactiveEnemiesIndices->Add(InstanceId);
}

void FEnemyData::Init(FVector Origin, float BaseHealth, FVector BaseDirection, float BaseSpeed, int32 BaseInstanceId)
{
	Transform.SetLocation(Origin);
	Health = BaseHealth;
	Direction = BaseDirection;
	Speed = BaseSpeed;
	InstanceId = BaseInstanceId;

	SetActive(true);
}

void FEnemyData::Kill()
{
	Transform = FTransform::Identity;
	Health = 0;
	Direction = FVector::ZeroVector;
	Speed = 0;
	InstanceId = -1;

	SetActive(false);
}

void FEnemyData::UpdatePosition(float DeltaTime, int32& TempInstanceId, FTransform& TempTransform,
                                float& TempDistanceFromOrigin)
{
	float Damage = 0;
	float DecreaseSpeed = 0;

	for (int i = Statuses.Num() - 1; i >= 0; i--)
	{
		if (Statuses[i].UpdateStatus(DeltaTime, Damage, DecreaseSpeed))
		{
			FName StatusName = Statuses[i].Name;
			
			Statuses.RemoveAt(i);
			
			StatusCount[StatusName]--;
			if (StatusCount[StatusName] == 0)
			{
				StatusCount.Remove(StatusName);
			}
		}
	}

	ApplyDamage(Damage);
	
	float ElapsedDistance = DeltaTime * FMath::Clamp(Speed - DecreaseSpeed, 0, 1);
	DistanceFromOrigin += ElapsedDistance;
	Transform.AddToTranslation(Direction * ElapsedDistance);

	TempInstanceId = InstanceId;
	TempDistanceFromOrigin = DistanceFromOrigin;
	TempTransform = Transform;
}

void FEnemyData::AddStatus(FStatus NewStatus)
{
	FName StatusName = NewStatus.Name;
	
	if (NewStatus.bCanStack || !StatusCount.Contains(StatusName))
	{
		Statuses.Add(NewStatus);
		StatusCount.FindOrAdd(StatusName)++;
	}
}
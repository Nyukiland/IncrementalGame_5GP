#include "IGEnemyData.h"

void FEnemyData::ApplyDamage(float Damage)
{
	if (Health <= 0)
		return;
		
	Health -= Damage;
	if (Health <= 0) Death();
}

void FEnemyData::Death()
{
		
}

void FEnemyData::SetActive(bool bNewActive)
{
	if (bIsActive_Internal == bNewActive)
		return;
	
	if (!ActiveEnemiesIndices)
		return;
		
	if (!EnemiesData->IsValidIndex(InstanceId))
		return;

	bIsActive_Internal = bNewActive;

	if (bIsActive_Internal)
	{
		if (!ActiveEnemiesIndices->Contains(InstanceId))
			ActiveEnemiesIndices->Add(InstanceId);
	}
	else
		ActiveEnemiesIndices->Remove(InstanceId);
}

void FEnemyData::Init(FVector Origin, float BaseHealth, FVector BaseDirection, float BaseSpeed)
{
	Transform.SetLocation(Origin);
	Health = BaseHealth;
	Direction = BaseDirection;
	Speed = BaseSpeed;
}

void FEnemyData::UpdatePosition(float DeltaTime, int32& TempInstanceId, FTransform& TempTransform, float& TempDistanceFromOrigin)
{
	float elapsedDistance = DeltaTime * Speed;
	DistanceFromOrigin += elapsedDistance;
	Transform.AddToTranslation(Direction * elapsedDistance);
	
	TempInstanceId = InstanceId;
	TempDistanceFromOrigin = DistanceFromOrigin;
	TempTransform = Transform;
}

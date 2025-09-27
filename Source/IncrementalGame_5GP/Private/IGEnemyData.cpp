#include "IGEnemyData.h"

void FEnemyData::ApplyDamage(float Damage)
{
	if (Life <= 0)
		return;
		
	Life -= Damage;
	if (Life <= 0) Death();
}

void FEnemyData::Death()
{
		
}

void FEnemyData::SetActive(bool bNewActive)
{
	if (bIsActive_Internal == bNewActive)
		return;
	
	if (!ActiveEnemiesIndices || !GameManager.IsValid())
		return;
		
	if (!EnemiesData->IsValidIndex(InstanceId))
		return;

	bIsActive_Internal = bNewActive;

	if (bIsActive_Internal)
	{
		if (!ActiveEnemiesIndices->Contains(InstanceId))
			ActiveEnemiesIndices->Add(InstanceId);
			
		GameManager->InsertIntoGrid(InstanceId, Transform.GetLocation());
	}
	else
	{
		ActiveEnemiesIndices->Remove(InstanceId);
		GameManager->RemoveFromGrid(InstanceId, Transform.GetLocation());
	}
}

void FEnemyData::UpdatePosition(FTransform transform)
{
	Transform = transform;

	// EnemiesPositions[InstanceId] = Transform.GetLocation();
	//je n'arrive pas à update la position dans EnemiesPositions
}

void FEnemyData::UpdatePosition(FVector position)
{
	Transform.SetLocation(position);

	//je n'arrive pas à update la position dans EnemiesPositions
	// EnemiesPositions[InstanceId] = position;
}

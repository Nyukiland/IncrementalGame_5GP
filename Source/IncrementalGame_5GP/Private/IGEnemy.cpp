#include "IGEnemy.h"
#include "IGGameManager.h"
#include "IGMathEquations.h"

AIGEnemy::AIGEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	CurrentLife = 0;
	CurrentDefenseValue = 0;
	CurrentSpeed = 0;
	CurrentDirection = FVector::ZeroVector;
	bIsActive = false;
}

void AIGEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AIGEnemy::InitEnemy(UIGGameManager* GameManager)
{
	if (!Manager)
	{
		UE_LOG(LogTemp, Error, TEXT("[Enemy] Missing Manager, can't Init properly on %s"), *this->GetName());
		return;
	}
	
	Manager = GameManager;
}

void AIGEnemy::EnableEnemy(FVector StartPos, FVector Direction, float Time)
{
	SetActorLocation(StartPos);

	CurrentDirection = Direction.GetSafeNormal();

	CurrentLife = LifeCurve->GetValue(Time);
	CurrentSpeed = SpeedCurve->GetValue(Time);

	bIsActive = true;
}

void AIGEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bIsActive)
		return;

	AddActorWorldOffset(CurrentDirection * DeltaTime);
}

void AIGEnemy::TakeDamage(float Damage)
{
	CurrentLife -= Damage;
	
	if (CurrentLife <= 0)
		DisableEnemy();
}

void AIGEnemy::DisableEnemy()
{
	if (!Manager)
	{
		UE_LOG(LogTemp, Error, TEXT("[Enemy] Missing Manager, can't call disable on %s"), *this->GetName());
		return;
	}
	
	bIsActive = false;
	Manager->EnemyWentInactive(this);
}
#include "IGGameController.h"

AIGGameController::AIGGameController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AIGGameController::BeginPlay()
{
	Super::BeginPlay();
}

void AIGGameController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIGGameController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
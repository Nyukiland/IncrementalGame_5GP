#include "IGStateComponent.h"

UIGStateComponent::UIGStateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UIGStateComponent::InitStateComponent_Implementation(AIGGameController* Controller)
{
	Owner = Controller;
}

void UIGStateComponent::EnableStateComponent_Implementation()
{
}

void UIGStateComponent::DisableStateComponent_Implementation()
{
}

void UIGStateComponent::TickStateComponent_Implementation(float DeltaTime)
{
}
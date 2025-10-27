#include "IGStateComponent.h"

UIGStateComponent::UIGStateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UIGStateComponent::InitStateComponent_Implementation(AIGPlayer* Controller)
{
	Owner = Controller;
}

void UIGStateComponent::EnableStateComponent_Implementation()
{
	bActive = true;
}

void UIGStateComponent::DisableStateComponent_Implementation()
{
	bActive = false;
}

void UIGStateComponent::TickStateComponent_Implementation(float DeltaTime)
{
}
#include "IGState.h"

void UIGState::OnEnter_Implementation(AIGPlayer* GameController)
{
	Owner = GameController;
}

void UIGState::OnExit_Implementation()
{

}

void UIGState::OnTick_Implementation(float DeltaTime)
{

}
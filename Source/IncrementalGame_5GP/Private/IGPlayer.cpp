#include "IGPlayer.h"
#include "Components/ActorComponent.h"
#include "IGStateComponent.h"
#include "IGState.h"

void AIGPlayer::BeginPlay()
{
	Super::BeginPlay();

	ChangeState(DefaultState);

	TArray<UActorComponent*> Components;
	GetComponents(Components);

	for (UActorComponent* Comp : Components)
	{
		if (UIGStateComponent* StateComp = Cast<UIGStateComponent>(Comp))
		{
			StateComponents.Add(StateComp);
			StateComp->InitStateComponent(this);

			for (TSubclassOf<UIGStateComponent> DefaultComp : DefaultActiveComponent)
			{
				if (StateComp->IsA(DefaultComp))
				{
					StateComponents.Swap(StateComponents.Num() - 1, ActiveComponentCount);
					ActiveComponentCount++;
					break;
				}
			}
		}
	}

	for (int i = 0; i < ActiveComponentCount; i++)
	{
		if (StateComponents[i])
			StateComponents[i]->EnableStateComponent();
	}
}

void AIGPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentState)
	{
		CurrentState->OnTick(DeltaTime);
	}

	for (int i = 0; i < ActiveComponentCount; i++)
	{
		if (StateComponents[i])
			StateComponents[i]->TickStateComponent(DeltaTime);
	}
}

void AIGPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UIGStateComponent* AIGPlayer::GetStateComponentByClass(TSubclassOf<UIGStateComponent> ComponentClass)
{
	int I = 0;
	return GetStateComponentByClass(ComponentClass, I);
}

UIGStateComponent* AIGPlayer::GetStateComponentByClass(TSubclassOf<UIGStateComponent> ComponentClass, int& Index)
{
	Index = -1;

	for (int i = 0; i < StateComponents.Num(); i++)
	{
		UIGStateComponent* Comp = StateComponents[i];

		if (Comp && Comp->IsA(ComponentClass))
		{
			Index = i;
			return Comp;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Failed to get component of class: %s"), *ComponentClass->GetName());

	return nullptr;
}

void AIGPlayer::ActivateStateComponent(TSubclassOf<UIGStateComponent> ComponentClass)
{
	int I = 0;
	UIGStateComponent* Comp = GetStateComponentByClass(ComponentClass, I);
	ActivateStateComponent(Comp, I);
}

void AIGPlayer::ActivateStateComponent(UIGStateComponent* Comp, int Index)
{
	if (!Comp || Index < 0 || Index > StateComponents.Num())
		return;

	StateComponents.Swap(Index, ActiveComponentCount);
	Comp->EnableStateComponent();
	ActiveComponentCount++;
}

void AIGPlayer::DeactivateStateComponent(TSubclassOf<UIGStateComponent> ComponentClass)
{
	int I = 0;
	UIGStateComponent* Comp = GetStateComponentByClass(ComponentClass, I);
	DeactivateStateComponent(Comp, I);
}

void AIGPlayer::DeactivateStateComponent(UIGStateComponent* Comp, int Index)
{
	if (!Comp || Index < 0 || Index > StateComponents.Num())
		return;

	StateComponents.Swap(Index, ActiveComponentCount - 1);
	Comp->DisableStateComponent();
	ActiveComponentCount--;
}

void AIGPlayer::ChangeState(TSubclassOf<UIGState> StateClass)
{
	if (!*StateClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("ChangeState called with null class."));
		return;
	}

	if (CurrentState)
	{
		CurrentState->OnExit();
		CurrentState = nullptr;
	}

	UIGState* NewState = NewObject<UIGState>(this, StateClass);
	if (!NewState)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create state of class: %s"), *StateClass->GetName());
		return;
	}

	NewState->OnEnter(this);
	CurrentState = NewState;
}

void AIGPlayer::CallOnEvent(const FString& Value)
{
	OnEventCalled.Broadcast(Value);
}

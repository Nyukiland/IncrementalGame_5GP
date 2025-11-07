#include "IGPlayer.h"

#include "IGGameManager.h"
#include "Components/ActorComponent.h"
#include "IGStateComponent.h"

void AIGPlayer::BeginPlay()
{
	Super::BeginPlay();

	CurrentPrestige = 0;
	
	if (!PrestigeKillNeededMathSubClass)
	{
		UE_LOG(LogTemp, Error, TEXT("[IGPlayer] PrestigeKillNeededSubClass not properly set"))
	}
	else
	{
		PrestigeKillNeededMath = NewObject<UIGMathEquations>(this, PrestigeKillNeededMathSubClass);
		PrestigeKillNeeded = PrestigeKillNeededMath->GetValue(CurrentPrestige);
	}

	if (!SlotCountMathSubClass)
	{
		UE_LOG(LogTemp, Error, TEXT("[IGPlayer] SlotCountMathSubClass not properly set"))
	}
	else
	{
		SlotCountMath = NewObject<UIGMathEquations>(this, SlotCountMathSubClass);	
		MaxSlotCount = SlotCountMath->GetValue(CurrentPrestige);
	}
	
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

	if (UIGGameManager* GameManager = GetWorld()->GetSubsystem<UIGGameManager>())
	{
		GameManager->OnEnemyDeath.AddDynamic(this, &AIGPlayer::IncreaseKillCount);
		GameManager->OnLoose.AddDynamic(this, &AIGPlayer::ResetGame);
	}
}

void AIGPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

	if (ActiveComponentCount < StateComponents.Num())
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

void AIGPlayer::CallOnEvent(FString Value)
{
	OnEventCalled.Broadcast(Value);
}

bool AIGPlayer::CheckPrestigeUpgrade(int PrestigeKillCount)
{
	return PrestigeKillCount >= PrestigeKillNeeded;
}

bool AIGPlayer::CheckSlotFull()
{
	return ActiveComponentCount - DefaultActiveComponent.Num() < MaxSlotCount;
}

void AIGPlayer::UpgradePrestige()
{
	CurrentPrestige += 1;
	ResetGame();
}

void AIGPlayer::ResetGame()
{
	GetWorld()->GetSubsystem<UIGGameManager>()->ResetManager();

	if (PrestigeKillNeededMath)
		PrestigeKillNeeded = PrestigeKillNeededMath->GetValue(CurrentPrestige);

	if (SlotCountMath)
		MaxSlotCount = (int)SlotCountMath->GetValue(CurrentPrestige);

	for (int i = ActiveComponentCount - 1; i >= 0; i--)
	{
		UIGStateComponent* Component = StateComponents[i];
		
		if (!Component)
			continue;
		
		Component->ResetComponent();

		bool ShouldReset = true;
		
		for (TSubclassOf<UIGStateComponent> DefaultComp : DefaultActiveComponent)
		{
			if (Component->IsA(DefaultComp))
			{
				ShouldReset = false;
				break;
			}
		}

		if (ShouldReset)
			DeactivateStateComponent(Component, i);
	}

	KillCount = 0;
}

void AIGPlayer::IncreaseKillCount(const FVector& Value)
{
	KillCount++;
}
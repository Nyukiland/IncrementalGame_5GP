#include "IGProjectileManagerComponent.h"
#include "IGPlayer.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

FProjectileData::FProjectileData()
{
	ID = "NONE";
	Instance = -1;
	
	StartPos = FVector(1, 1, 1);
	EndPos = FVector(1, 1, 1);

	StartScale = FVector(1, 1, 1);
	EndScale = FVector(1, 1, 1);

	Rotation = FRotator(0,0,0);
	
	Timer = 0;
	Duration = 0;
	Hold = 0;
}

FProjectileData::FProjectileData(FString Identifier, int InstanceIndex, FVector Start, FVector End, float DurationValue)
{
	ID = Identifier;
	Instance = InstanceIndex;
	StartPos = Start;
	EndPos = End;
	Duration = DurationValue;

	Timer = 0;
	Rotation = UKismetMathLibrary::FindLookAtRotation(Start, End);
	
	Hold = 0;
	StartScale = FVector(1, 1, 1);
	EndScale = FVector(1, 1, 1);
}

FProjectileData::FProjectileData(FString Identifier, int InstanceIndex, FVector Start, FVector End, FVector ScaleStart,
	FVector ScaleEnd, float DurationValue, float HoldValue)
{
	ID = Identifier;
	Instance = InstanceIndex;
	StartPos = Start;
	EndPos = End;
	StartScale = ScaleStart;
	EndScale = ScaleEnd;
	Duration = DurationValue;
	Hold = HoldValue;

	Timer = 0;
	Rotation = UKismetMathLibrary::FindLookAtRotation(Start, End);
}

bool FProjectileData::Update(float DeltaTime, FVector& CurrentPos, FVector& CurrentScale, FRotator& CurrentRotation)
{
	//TODO
	
	return true;
}

void UIGProjectileManagerComponent::InitStateComponent_Implementation(AIGPlayer* Controller)
{
	ProjectileMeshInstances = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedMesh"));
	ProjectileMeshInstances->SetupAttachment(Owner->GetRootComponent());
	ProjectileMeshInstances->RegisterComponent();
	
	ProjectileMeshInstances->SetStaticMesh(ProjectileMesh);
	ProjectileMeshInstances->NumCustomDataFloats = 4;
}

void UIGProjectileManagerComponent::EnableStateComponent_Implementation()
{
	ProjectilesDatas.Empty();
}

void UIGProjectileManagerComponent::TickStateComponent_Implementation(float DeltaTime)
{
	for (int i = ProjectilesDatas.Num() - 1; i >= 0; i--)
	{
		FVector Pos;
		FVector Scale;
		FRotator Rot;

		if (ProjectilesDatas[i].Update(DeltaTime, Pos, Scale, Rot))
		{
			ProjectilesDatas.RemoveAt(i);
		}
		
		FTransform NewTransform(Rot, Pos, Scale);
		ProjectileMeshInstances->UpdateInstanceTransform(ProjectilesDatas[i].Instance, NewTransform, false, true);
	}

	ProjectileMeshInstances->MarkRenderStateDirty();
}

void UIGProjectileManagerComponent::ResetComponent_Implementation()
{
	ProjectilesDatas.Empty();
}

void UIGProjectileManagerComponent::AddProjectile(FString ID, FVector Start, FVector End, float DurationValue,
                                                  FColor Color)
{
	//TODO
	
	int32 Index = ProjectileMeshInstances->AddInstance(Owner->GetTransform());
	ProjectileMeshInstances->SetCustomDataValue(Index, 0, Color.R, false);
	ProjectileMeshInstances->SetCustomDataValue(Index, 1, Color.G, false);
	ProjectileMeshInstances->SetCustomDataValue(Index, 2, Color.B, false);
	ProjectileMeshInstances->SetCustomDataValue(Index, 3, Color.A, false);

	FProjectileData Data = FProjectileData(ID, Index, Start, End, DurationValue);
	ProjectilesDatas.Add(Data);
}

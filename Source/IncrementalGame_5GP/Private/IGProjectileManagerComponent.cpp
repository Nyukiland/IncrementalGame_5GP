#include "IGProjectileManagerComponent.h"
#include "IGPlayer.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

FProjectileData::FProjectileData()
{
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

FProjectileData::FProjectileData(int InstanceIndex, FVector Start, FVector End, float Size, float DurationValue, float HoldValue)
{
	Instance = InstanceIndex;
	StartPos = Start;
	EndPos = End;
	Duration = DurationValue;

	Timer = 0;
	Rotation = UKismetMathLibrary::FindLookAtRotation(Start, End);
	
	Hold = HoldValue;
	StartScale = FVector::One() * Size;
	EndScale = FVector::One() * Size;
}

FProjectileData::FProjectileData(int InstanceIndex, FVector Start, FVector End, FVector ScaleStart,
	FVector ScaleEnd, float DurationValue, float HoldValue)
{
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
	Timer += DeltaTime;

	float T = FMath::Clamp(Timer / Duration, 0.0f, 1.0f);

	CurrentPos = FMath::Lerp(StartPos, EndPos, T);
	CurrentScale = FMath::Lerp(StartScale, EndScale, T);

	CurrentRotation = Rotation;
	
	return Timer < Duration + Hold;
}

void UIGProjectileManagerComponent::InitStateComponent_Implementation(AIGPlayer* Controller)
{
	Super::InitStateComponent_Implementation(Controller);
	
	ProjectileMeshInstances = NewObject<UInstancedStaticMeshComponent>(this);
	ProjectileMeshInstances->SetupAttachment(Owner->GetRootComponent());
	ProjectileMeshInstances->RegisterComponent();
	
	if (PlaneMesh)
	{
		ProjectileMeshInstances->SetStaticMesh(PlaneMesh);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[IGProjectileManagerComponent] PlaneMesh not properly set up"));
		return;
	}

	if (ProjectileVisu && BaseMaterial)
	{
		ProjectileMeshInstances->NumCustomDataFloats = 3;
		UMaterialInstanceDynamic* DynMat = UMaterialInstanceDynamic::Create(BaseMaterial, this);
		DynMat->SetTextureParameterValue(FName("SpriteTexture"), ProjectileVisu);
		ProjectileMeshInstances->SetMaterial(0, DynMat);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[IGProjectileManagerComponent] ProjectileVisu or BaseMaterial not properly set up"));
		return;
	}

	ProjectileMeshInstances->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UIGProjectileManagerComponent::EnableStateComponent_Implementation()
{
	ProjectilesDatas.Empty();
}

void UIGProjectileManagerComponent::TickStateComponent_Implementation(float DeltaTime)
{
	for (int32 i = ProjectilesDatas.Num() - 1; i >= 0; i--)
	{
		FVector Pos;
		FVector Scale;
		FRotator Rot;

		bool bStillActive = ProjectilesDatas[i].Update(DeltaTime, Pos, Scale, Rot);

		if (!bStillActive)
		{
			AvailableInstanceIndices.Add(ProjectilesDatas[i].Instance);

			FTransform NewTransform(Rot, FVector(-1000, -1000, -1000), FVector(0, 0, 0));
			ProjectileMeshInstances->UpdateInstanceTransform(ProjectilesDatas[i].Instance, NewTransform, false, true);
			ProjectilesDatas.RemoveAt(i);

			continue;
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

void UIGProjectileManagerComponent::AddProjectile(FVector Start, FVector End, float Size, float DurationValue, float Hold, FColor Color)
{
	int32 Index = CreateGetProjectile(FTransform(Start), Color);

	FProjectileData Data(Index, Start, End, Size, DurationValue, Hold);
	ProjectilesDatas.Add(Data);
}

void UIGProjectileManagerComponent::AddProjectile(FVector Pos, float EndScale, float DurationValue, float Hold, FColor Color)
{
	int32 Index = CreateGetProjectile(FTransform(Pos), Color);

	FProjectileData Data(Index, Pos, Pos, FVector::Zero(), FVector(EndScale, EndScale, EndScale), DurationValue, Hold);
	ProjectilesDatas.Add(Data);
}

void UIGProjectileManagerComponent::AddProjectile(FVector Start, float SideScale, FVector End, float DurationValue, float Hold,
	FColor Color)
{
	int32 Index = CreateGetProjectile(FTransform(Start), Color);

	FVector Dir = End - Start;
	float Length = Dir.Length();

	FVector StartPos = Start;
	FVector EndPos = Start + Dir * 0.5f;
	FVector StartScale = FVector(0.0f, SideScale, 1.0f);
	FVector EndScale = FVector(Length * 0.01f, SideScale, 1.0f);

	FProjectileData Data(Index, StartPos, EndPos, StartScale, EndScale, DurationValue, Hold);
	ProjectilesDatas.Add(Data);
}

int UIGProjectileManagerComponent::CreateGetProjectile(FTransform Pos, FColor Color)
{
	int32 Index;

	if (AvailableInstanceIndices.Num() > 0)
	{
		Index = AvailableInstanceIndices.Pop();
		ProjectileMeshInstances->UpdateInstanceTransform(Index, FTransform(Pos), false, true);
	}
	else
	{
		Index = ProjectileMeshInstances->AddInstance(FTransform(Pos));
	}

	ProjectileMeshInstances->SetCustomDataValue(Index, 0, Color.R / 255.0f, false);
	ProjectileMeshInstances->SetCustomDataValue(Index, 1, Color.G / 255.0f, false);
	ProjectileMeshInstances->SetCustomDataValue(Index, 2, Color.B / 255.0f, false);

	ProjectileMeshInstances->MarkRenderStateDirty();

	return Index;
}

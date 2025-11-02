#include "IGGameManagerInitializer.h"

#include "IGGameManager.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "MathEquation/IGMathEquations.h"

AIGGameManagerInitializer::AIGGameManagerInitializer()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AIGGameManagerInitializer::BeginPlay()
{
	Super::BeginPlay();

	if (!DecreaseZoneCurveSubClass || !EnemyHealthSubClass || !EnemySpeedSubClass
	|| !SpawnRateCurveSubClass)
	{
		UE_LOG(LogTemp, Error, TEXT("[IGGameManagerInitializer] CurveSubclass not properly set up"));
		return;
	}
	UIGMathEquations* DecreaseZoneCurve = NewObject<UIGMathEquations>(this, DecreaseZoneCurveSubClass);
	UIGMathEquations* EnemyHealth = NewObject<UIGMathEquations>(this, EnemyHealthSubClass);
	UIGMathEquations* EnemySpeed = NewObject<UIGMathEquations>(this, EnemySpeedSubClass);
	UIGMathEquations* SpawnRateCurve = NewObject<UIGMathEquations>(this, SpawnRateCurveSubClass);

	UInstancedStaticMeshComponent* EnemiesMeshInstances = NewObject<UInstancedStaticMeshComponent>(this);
	EnemiesMeshInstances->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	EnemiesMeshInstances->RegisterComponent();

	if (PlaneMesh)
	{
		EnemiesMeshInstances->SetStaticMesh(PlaneMesh);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[IGGameManagerInitializer] PlaneMesh not properly set up"));
		return;
	}

	if (EnemyVisu && BaseMaterial)
	{
		UMaterialInstanceDynamic* DynMat = UMaterialInstanceDynamic::Create(BaseMaterial, this);
		DynMat->SetTextureParameterValue(FName("SpriteTexture"), EnemyVisu);
		EnemiesMeshInstances->SetMaterial(0, DynMat);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[IGGameManagerInitializer] EnemyVisu or BaseMaterial not properly set up"));
		return;
	}

	EnemiesMeshInstances->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	EnemiesMeshInstances->SetCollisionProfileName(TEXT("EnemyOnly"));

	GetWorld()->GetSubsystem<UIGGameManager>()->InitializeManager(EnemiesMeshInstances,
		EnemyHealth, EnemySpeed, SpawnRateCurve, DecreaseZoneCurve,
		ZoneMaxRadius, ZoneMinRadius, InvincibilityFrame);
}

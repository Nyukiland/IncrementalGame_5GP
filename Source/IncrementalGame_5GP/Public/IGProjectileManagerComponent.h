#pragma once

#include "CoreMinimal.h"
#include "IGCapacityComponent.h"
#include "IGProjectileManagerComponent.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FProjectileData
{
	GENERATED_BODY()

public:
	FString ID;
	int Instance;

private:
	float Timer;
	FVector StartPos;
	FVector EndPos;

	FVector StartScale;
	FVector EndScale;

	FRotator Rotation;

	float Duration;
	float Hold;
	
public:
	FProjectileData();
	FProjectileData(FString Identifier, int InstanceIndex, FVector Start, FVector End, float DurationValue);
	FProjectileData(FString Identifier, int InstanceIndex, FVector Start, FVector End, FVector ScaleStart, FVector ScaleEnd, float DurationValue, float HoldValue);

	bool Update(float DeltaTime, FVector& CurrentPos, FVector& CurrentScale, FRotator& CurrentRotation);
};

UCLASS(Blueprintable)
class INCREMENTALGAME_5GP_API UIGProjectileManagerComponent : public UIGStateComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Manager")
	TObjectPtr<UTexture2D> ProjectileVisu;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile Manager")
	TObjectPtr<UStaticMesh> PlaneMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile Manager")
	TObjectPtr<UMaterialInterface> BaseMaterial;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Manager")
	TObjectPtr<UInstancedStaticMeshComponent> ProjectileMeshInstances;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Manager")
	TArray<FProjectileData> ProjectilesDatas;
	
public:
	virtual void InitStateComponent_Implementation(AIGPlayer* Controller) override;
	virtual void EnableStateComponent_Implementation() override;
	virtual void TickStateComponent_Implementation(float DeltaTime) override;
	virtual void ResetComponent_Implementation() override;

	void AddProjectile(FString ID, FVector Start, FVector End, float DurationValue, FColor Color);
};

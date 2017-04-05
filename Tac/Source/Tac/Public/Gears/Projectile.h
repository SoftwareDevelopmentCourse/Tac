// Copyright by GameDream.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TAC_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Collision mesh to observe hit event
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CollisionMesh;

private:
	// Projectile movement component launches actor as projectile
	UProjectileMovementComponent* ProjectileMovementComponent;
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
public:
	FORCEINLINE	UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovementComponent; }
	
public:
	// Activite the projectile
	void LaunchProjectile(float LaunchSpeed);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Damage)
	float DamageAmount;
};

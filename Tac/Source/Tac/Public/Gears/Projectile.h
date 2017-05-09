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
	USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

private:
	// Projectile movement component launches actor as projectile
	UProjectileMovementComponent* ProjectileMovementComponent;
	UFUNCTION(NetMulticast, Reliable)
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:
	FORCEINLINE	UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovementComponent; }
	
public:
	// Activite the projectile
	//UFUNCTION(Server, Reliable, WithValidation)
	void LaunchProjectile(FVector OutLaunchVelocity);
	AActor* OwnerGun;
	float GetLaunchSpeed();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Damage)
	float DamageAmount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Damage)
	float LaunchSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Damage)
	float DestroyDelay = 1.f;
};

// Copyright by GameDream.

#include "Tac.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollisionMesh"));
	RootComponent = CollisionMesh;
	CollisionMesh->SetNotifyRigidBodyCollision(true);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->bAutoActivate = false;

	DamageAmount = 30.f;
	LaunchSpeed = 10000.f;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	if (Hit.BoneName.IsValid())
	{
		//UE_LOG(LogTemp, Log, TEXT("%s"), *Hit.BoneName.ToString());
		TArray<TCHAR> HitName = Hit.BoneName.ToString().GetCharArray();
		UE_LOG(LogTemp, Error, TEXT("GG%i"), HitName.GetData());

	}
	Destroy();
}

void AProjectile::LaunchProjectile()
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
	ProjectileMovementComponent->Activate();

}

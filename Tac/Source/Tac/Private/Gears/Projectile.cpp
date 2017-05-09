// Copyright by GameDream.

#include "Tac.h"
#include "Projectile.h"
#include "VehicleDamageType.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetCollisionProfileName(TEXT("BlockAll"));
	RootComponent = CollisionSphere;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollisionMesh"));
	VisualMesh->SetupAttachment(RootComponent);
	VisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	VisualMesh->SetNotifyRigidBodyCollision(false);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetIsReplicated(true);
	ProjectileMovementComponent->bAutoActivate = false;

	DamageAmount = 30.f;
	LaunchSpeed = 10000.f;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit_Implementation(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	if (Hit.BoneName.IsValid())
	{
		float DamageFactor = 1.f;
		TArray<TCHAR> HitName = Hit.BoneName.ToString().GetCharArray();
		if (FString(5, HitName.GetData()) == FString(TEXT("PhysW")))
		{
			DamageFactor = 0.75f;
		}
		else if (HitName.GetData() == FString(TEXT("Engine")))
		{
			DamageFactor = 2.f;
		}
		UGameplayStatics::ApplyDamage(
		OtherActor,
		DamageAmount * DamageFactor,
		Instigator->GetController(),
		OwnerGun,
		UVehicleDamageType::StaticClass()
		);
	}
	Destroy();
}

/*
bool AProjectile::LaunchProjectile_Validate()
{
	return true;
}
*/

void AProjectile::LaunchProjectile(FVector OutLaunchVelocity)

{
	ProjectileMovementComponent->SetVelocityInLocalSpace(OutLaunchVelocity * LaunchSpeed);
	ProjectileMovementComponent->Activate();
	UE_LOG(LogTemp, Error, TEXT("%s"), *OutLaunchVelocity.ToString());
}

float AProjectile::GetLaunchSpeed()
{
	return LaunchSpeed;
}

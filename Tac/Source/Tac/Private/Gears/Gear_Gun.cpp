// Copyright by GameDream.

#include "Tac.h"
#include "Gear_Gun.h"
#include "Projectile.h"
#include "TacController.h"
#include "TacVehicle.h"


void AGear_Gun::Initialize(UStaticMeshComponent* GunMeshToSet)
{
	GunMesh = GunMeshToSet;
}

void AGear_Gun::OnLClickHit_Implementation(AActor* Target)
{
	if (HasAuthority())
	{
		Super::OnLClickHit(Target);
		if (Ammo > 0)
		{
			auto SpawnLocation = GunMesh->GetSocketLocation(TEXT("Fire"));
			auto SpawnRotation = GunMesh->GetSocketRotation(TEXT("Fire"));
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
			Projectile->Instigator = Cast<APawn>(Target);
			Projectile->OwnerGun = this;
			Projectile->CollisionSphere->IgnoreActorWhenMoving(Target, true);
			APawn* TacPawn = Cast<APawn>(GetAttachParentActor());
			ATacController* TC = Cast<ATacController>(TacPawn->Controller);
			UE_LOG(LogTemp, Error, TEXT("%s"), *TC->GetName());
			auto StartLocation = GunMesh->GetSocketLocation(TEXT("Fire")); 
			FVector LaunchVelocity = TC->Aimat(StartLocation, Projectile->GetLaunchSpeed());
			LaunchProjectile(Projectile, LaunchVelocity);
		}
	}
}

void AGear_Gun::LaunchProjectile(AProjectile* ProjectileToLaunch, FVector LaunchVelocity)
{
	ProjectileToLaunch->LaunchProjectile(LaunchVelocity);
}
// Copyright by GameDream.

#include "Tac.h"
#include "Gear_Gun.h"
#include "Projectile.h"

void AGear_Gun::Initialize(UStaticMeshComponent* GunMeshToSet)
{
	GunMesh = GunMeshToSet;
}

/*
bool AGear_Gun::OnLClickHit_Validate(AActor* Target)
{
	return true;
}
*/

void AGear_Gun::OnLClickHit_Implementation(AActor* Target)
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
		Projectile->LaunchProjectile();
	}
}
// Copyright by GameDream.

#include "Tac.h"
#include "Gear_Gun.h"
#include "Projectile.h"

void AGear_Gun::Initialize(UStaticMeshComponent* GunMeshToSet)
{
	GunMesh = GunMeshToSet;
}

void AGear_Gun::OnLClickHit(AActor* Target)
{
	Super::OnLClickHit(Target);
	if (Ammo > 0)
	{
		auto SpawnLocation = GunMesh->GetSocketLocation(TEXT("Fire"));
		auto SpawnRotation = GunMesh->GetSocketRotation(TEXT("Fire"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		Projectile->Instigator = Cast<APawn>(Target);
		Projectile->LaunchProjectile();
	}
}
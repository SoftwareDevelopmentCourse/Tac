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
	UE_LOG(LogTemp, Log, TEXT("%s,Shooooooting!"), *Target->GetName());
}
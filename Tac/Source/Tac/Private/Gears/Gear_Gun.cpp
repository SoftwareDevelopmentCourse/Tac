// Copyright by GameDream.

#include "Tac.h"
#include "Gear_Gun.h"
#include "Projectile.h"

AGear_Gun::AGear_Gun()
{
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	
}

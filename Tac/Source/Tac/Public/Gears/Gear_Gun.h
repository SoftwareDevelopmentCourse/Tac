// Copyright by GameDream.

#pragma once

#include "Gears/Gears.h"
#include "Gear_Gun.generated.h"

/**
 * 
 */

class AProjectile;

UCLASS()
class TAC_API AGear_Gun : public AGears
{
	GENERATED_BODY()

public:
	AGear_Gun();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Gear|Gun")
	UStaticMeshComponent* GunMesh;

private:
	TSubclassOf<AProjectile> ProjectileClass;
	
	
};

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
	UFUNCTION(BlueprintCallable, Category = "Gear|Gun")
	void Initialize(UStaticMeshComponent* GunMeshToSet);
	virtual void OnLClickHit(AActor* Target) override;
	

private:
	UPROPERTY(EditDefaultsOnly, Category = "Gear|Gun")
	TSubclassOf<AProjectile> ProjectileClass;

	UStaticMeshComponent* GunMesh;
	
	
};

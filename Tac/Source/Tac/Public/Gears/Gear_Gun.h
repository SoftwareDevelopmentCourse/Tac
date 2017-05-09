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
	UFUNCTION(Client, Reliable)
	virtual void OnLClickHit(AActor* Target) override;

	//UFUNCTION(NetMulticast, Reliable)
	void LaunchProjectile(AProjectile* ProjectileToLaunch, FVector LaunchVelocity);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gear|Gun")
	float ArmorPenetration = 0.5f;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gear|Gun")
	int32 Ammo = 10;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Gear|Gun")
	TSubclassOf<AProjectile> ProjectileClass;

	UStaticMeshComponent* GunMesh;



	
	
};

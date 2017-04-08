// Copyright by GameDream.

#pragma once

#include "GameFramework/DamageType.h"
#include "VehicleDamageType.generated.h"

/**
 * 
 */
UCLASS()
class TAC_API UVehicleDamageType : public UDamageType
{
	GENERATED_BODY()

public:
	UVehicleDamageType();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float ArmorPenetration;
	
	
};

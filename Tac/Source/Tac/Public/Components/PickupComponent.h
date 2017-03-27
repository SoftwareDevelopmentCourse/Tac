// Copyright by GameDream.

#pragma once

#include "Components/ActorComponent.h"
#include "PickupComponent.generated.h"

class UGearManagementComponent;
class ATacVehicle;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TAC_API UPickupComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickupComponent();

	/** Sets owner's properties for component's use */
	ATacVehicle* OwnerVehicle;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/** Try to pick up gears and take it */
	void Pickup();
	
	/** For storaging owner tac's pick up capsule */
	UCapsuleComponent* PickupCapsule;
	
};

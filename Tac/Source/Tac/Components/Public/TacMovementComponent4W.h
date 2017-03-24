// Copyright by GameDream.

#pragma once

#include "WheeledVehicleMovementComponent4W.h"
#include "TacMovementComponent4W.generated.h"

/**
 * 
 */
UCLASS()
class TAC_API UTacMovementComponent4W : public UWheeledVehicleMovementComponent4W
{
	GENERATED_BODY()
	
public:
	UTacMovementComponent4W();

	// Called from the pathfinding logic by the AI controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	
	UPROPERTY(VisibleAnywhere, Category = Setup)
	float ForwardSpeed;
	UPROPERTY(VisibleAnywhere, Category = Setup)
	float RightSpeed;
	
};

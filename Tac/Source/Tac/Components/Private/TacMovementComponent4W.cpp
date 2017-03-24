// Copyright by GameDream.

#include "Tac.h"
#include "Components/Public/TacMovementComponent4W.h"
#include "Player/Public/TacVehicle.h"

UTacMovementComponent4W::UTacMovementComponent4W()
{
	ForwardSpeed = 1.f;
	RightSpeed = 1.f;
}


void UTacMovementComponent4W::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super as we're replacing the functionality

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	UE_LOG(LogTemp, Warning, TEXT("%f"), ForwardThrow);
	ATacVehicle* TacPawn = Cast<ATacVehicle>(GetOwner());
	if (!ensure(TacPawn)) { return; }
	TacPawn->MoveForward(ForwardThrow * ForwardSpeed);
	TacPawn->MoveRight(RightThrow * RightSpeed);
}


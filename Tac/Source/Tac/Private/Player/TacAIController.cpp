// Copyright by GameDream.

#include "Tac.h"
#include "TacAIController.h"
#include "TacVehicle.h"

ATacAIController::ATacAIController()
{
	AcceptanceRadius = 100.f;
}


void ATacAIController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	
	auto PlayerControlledTac = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(PlayerControlledTac)) { return; }
	// Uses inherent function
	MoveToActor(PlayerControlledTac, AcceptanceRadius);
}

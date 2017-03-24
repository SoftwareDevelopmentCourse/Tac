// Copyright by GameDream.

#include "Tac.h"
#include "Player/Public/TacAIController.h"
#include "Player/Public/TacVehicle.h"

ATacAIController::ATacAIController()
{
	AcceptanceRadius = 100.f;
}


void ATacAIController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	
	auto PlayerControlledTac = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(PlayerControlledTac)) { return; }
	MoveToActor(PlayerControlledTac, AcceptanceRadius);
}

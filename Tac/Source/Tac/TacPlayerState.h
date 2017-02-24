// Copyright by GameDream.

#pragma once

#include "GameFramework/PlayerState.h"
#include "TacVehicle.h"
#include "TacPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TAC_API ATacPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ATacPlayerState();
	
	TArray<FGear> GetGears();
	void SetGears(TArray<FGear> GearsToSet);
	void AddGear(FGear GearToAdd);
	void EmptyGears();

	FTransform GetTacTransform();
	void SetTacTransform(FTransform TransformToSet);

private:
	TArray<FGear> Gears;
	FTransform TacTransform;
	
	
};

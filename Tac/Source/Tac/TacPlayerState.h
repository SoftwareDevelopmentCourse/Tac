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
	UPROPERTY(VisibleAnywhere, Category = "Gear")
	TArray<FGear> Gears;
	
	
};

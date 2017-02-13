// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Tac.h"
#include "TP_VehicleAdv.h"
#include "TP_VehicleAdvGameMode.h"
#include "TP_VehicleAdvPawn.h"
#include "TP_VehicleAdvHud.h"

ATP_VehicleAdvGameMode::ATP_VehicleAdvGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Adv/BP_VehicleAdvPawn"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	HUDClass = ATP_VehicleAdvHud::StaticClass();
}

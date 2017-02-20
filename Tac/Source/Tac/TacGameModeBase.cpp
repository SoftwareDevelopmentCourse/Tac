// Copyright by GameDream.

#include "Tac.h"
#include "TacGameModeBase.h"


ATacGameModeBase::ATacGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> TacBP(TEXT("/Game/Tac/MyTacVehicle"));
	DefaultPawnClass = TacBP.Class;
}

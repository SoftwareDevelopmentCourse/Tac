// Copyright by GameDream.

#include "Tac.h"
#include "Gear_Ejector.h"


void AGear_Ejector::OnShiftHit(AActor* Target)
{
	Super::OnShiftHit(Target);
	UE_LOG(LogTemp, Warning, TEXT("Booooooost!"));
}


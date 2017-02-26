// Copyright by GameDream.

#include "Tac.h"
#include "TacPlayerState.h"
#include "Kismet/GameplayStatics.h"

TArray<FGear> ATacPlayerState::GetGears()
{
	return Gears;
}

FGear ATacPlayerState::GetGear(int32 GearIndex)
{
	if (Gears.IsValidIndex(GearIndex))
	{
		return Gears[GearIndex];
	}
	else
	{
		FGear Default;
		Default.Gear = UStaticMeshComponent::StaticClass();
		Default.Socket = EGearSocket::ELeft;
		return Default;
	}
}

void ATacPlayerState::SetGears(TArray<FGear> GearsToSet)
{
	Gears = GearsToSet;
}

void ATacPlayerState::AddGear(FGear GearToAdd)
{
	Gears.Add(GearToAdd);
}

void ATacPlayerState::EmptyGears()
{
	Gears.Empty();
}

FTransform ATacPlayerState::GetTacTransform()
{
	return TacTransform;
}

void ATacPlayerState::SetTacTransform(FTransform TransformToSet)
{
	TacTransform = TransformToSet;
}

FString ATacPlayerState::GetPlayerName()
{
	return MyPlayerName;
}

void ATacPlayerState::SetName(FString NameToSet)
{
	MyPlayerName = NameToSet;
}

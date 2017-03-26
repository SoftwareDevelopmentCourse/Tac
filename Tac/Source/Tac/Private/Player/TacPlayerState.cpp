// Copyright by GameDream.

#include "Tac.h"
#include "TacPlayerState.h"
#include "Gears.h"
#include "Kismet/GameplayStatics.h"

TArray<TSubclassOf<AGears>> ATacPlayerState::GetGears()
{
	return Gears;
}

TSubclassOf<AGears> ATacPlayerState::GetGear(int32 GearIndex)
{
	if (Gears.IsValidIndex(GearIndex))
	{
		return Gears[GearIndex];
	}
	else
	{
		return AGears::StaticClass();
	}
}

FString ATacPlayerState::GetSocketName(int32 SocketIndex)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGearSocket"), true);
	if (!EnumPtr) return FString("Invalid");
	return EnumPtr->GetEnumName(SocketIndex);
}

void ATacPlayerState::SetGears(TArray<TSubclassOf<AGears>> GearsToSet)
{
	Gears = GearsToSet;
}

void ATacPlayerState::AddGear(TSubclassOf<AGears> GearToAdd)
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

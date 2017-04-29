// Copyright by GameDream.

#include "Tac.h"
#include "TacPlayerState.h"
#include "Gears.h"
#include "Kismet/GameplayStatics.h"

ATacPlayerState::ATacPlayerState()
{
	bReplicates = true;
}

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
	else // If has no gears, return null gear
	{
		return AGears::StaticClass();
	}
}

FString ATacPlayerState::GetSocketName(int32 GearIndex)
{
	// Way of getting socket name: https://wiki.unrealengine.com/Enums_For_Both_C%2B%2B_and_BP
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGearSocket"), true);
	if (!EnumPtr) return FString("Invalid");
	int32 EnumNum;
	if (!Gears.IsValidIndex(GearIndex)) { return TEXT("DEFAULT_SOCKET"); }
	switch (Gears[GearIndex].GetDefaultObject()->GearSocket)
	{
	case EGearSocket::ENull:
		EnumNum = 0;
		break;
	case EGearSocket::ELeft:
		EnumNum = 1;
		break;
	case EGearSocket::ERight:
		EnumNum = 2;
		break;
	case EGearSocket::EFront:
		EnumNum = 3;
		break;
	case EGearSocket::EBack:
		EnumNum = 4;
		break;
	default:
		EnumNum = 5;
		break;
	}
	return EnumPtr->GetEnumName(EnumNum);
}

void ATacPlayerState::SetGears(TArray<TSubclassOf<AGears>> GearsToSet)
{
	Gears = GearsToSet;
}

void ATacPlayerState::AddGear(int32 GearIndex, TSubclassOf<AGears> GearToAdd)
{
	Gears[GearIndex] = GearToAdd;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Gears[0]->GetName());
}

void ATacPlayerState::EmptyGears()
{
	Gears.Empty();
	Gears.SetNum(4);
	GearsAmount = 0;
}

FString ATacPlayerState::GetPlayerName()
{
	return MyPlayerName;
}

FName ATacPlayerState::GetGearName(int32 GearIndex)
{
	if (Gears.IsValidIndex(GearIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("Access"));
		return Gears[GearIndex].GetDefaultObject()->GearName;
	}
	else // If has no gears, return null gear
	{
		UE_LOG(LogTemp, Warning, TEXT("No access"))
		return FName("DEFAULT_NAME");
	}
}

void ATacPlayerState::SetName(FString NameToSet)
{
	MyPlayerName = NameToSet;
}

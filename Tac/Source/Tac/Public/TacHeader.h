// Copyright by GameDream.

#pragma once
#include "GearComponent.h"
#include "TacHeader.generated.h"

UENUM(BlueprintType)
enum class EGearSocket : uint8
{
	ENull,
	ELeft,
	ERight,
	EFront,
	EBack
};

USTRUCT()
struct FGear
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gear)
	TSubclassOf<UGearComponent> Gear;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gear)
	EGearSocket Socket;

	FString GetSocketName()
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGearSocket"), true);
		if (!EnumPtr) return FString("Invalid");
		return EnumPtr->GetEnumName((int32)Socket);
	}

	FGear()
	{
		Gear = NULL;
		Socket = EGearSocket::EBack;
	}

};
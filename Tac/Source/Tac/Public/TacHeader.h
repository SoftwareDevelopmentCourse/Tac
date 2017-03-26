// Copyright by GameDream.

#pragma once
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

UENUM(BlueprintType)
enum class EGearType : uint8
{
	EProtector,
	EShoot,
	EThrow,
	EBoost,
	EJump
};

/*
	USTRUCT(BlueprintType)
struct TSubclassOf<AGears>
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gear)
	FName GearName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gear)
	EGearSocket Socket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gear)
	EGearType Type;

	FString GetSocketName()
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGearSocket"), true);
		if (!EnumPtr) return FString("Invalid");
		return EnumPtr->GetEnumName((int32)Socket);
	}

	TSubclassOf<AGears>()
	{
		GearName = TEXT("NULL");
		Socket = EGearSocket::EBack;
		Type = EGearType::EProtector;
	}

};
*/

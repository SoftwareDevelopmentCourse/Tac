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

UENUM(BlueprintType)
enum class EGearType : uint8
{
	EProtector,
	EShoot,
	EThrow,
	EBoost,
	EJump
};

USTRUCT(BlueprintType)
struct FGear
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gear)
	FName GearName;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gear)
	UGearComponent* GearComp;

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

	FGear()
	{
		GearName = TEXT("NULL");
		GearComp = NULL;
		Socket = EGearSocket::EBack;
		Type = EGearType::EProtector;
	}

};
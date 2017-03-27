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

// Copyright by GameDream.

#pragma once

#include "GameFramework/SaveGame.h"
#include "TacVehicle.h"
#include "TacSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TAC_API UTacSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = Save)
	FString PlayerName;
	
	UPROPERTY(VisibleAnywhere, Category = Save)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Save)
	uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Save)
	TArray<FGear> Gears;

	UPROPERTY(VisibleAnywhere, Category = Save)
	FTransform TacTransform;

	UTacSaveGame();
	
};

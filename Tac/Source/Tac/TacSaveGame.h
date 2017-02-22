// Copyright by GameDream.

#pragma once

#include "GameFramework/SaveGame.h"
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

	UTacSaveGame();
	
};

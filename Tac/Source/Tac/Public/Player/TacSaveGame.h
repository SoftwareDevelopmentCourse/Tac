// Copyright by GameDream.

#pragma once

#include "GameFramework/SaveGame.h"
#include "TacVehicle.h"
#include "TacHeader.h"
#include "TacSaveGame.generated.h"

class AGears;
/**
 * 
 */
UCLASS()
class TAC_API UTacSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	/** Player's states that will be saved */
	UPROPERTY(VisibleAnywhere, Category = Save)
	FString PlayerName;
	
	UPROPERTY(VisibleAnywhere, Category = Save)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Save)
	uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Save)
	TArray<TSubclassOf<AGears>> Gears;

	/** No need to record player transform
	UPROPERTY(VisibleAnywhere, Category = Save)
	FTransform TacTransform;
	*/


	UTacSaveGame();
	
};

// Copyright by GameDream.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TacController.generated.h"

/**
 * 
 */
UCLASS()
class TAC_API ATacController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATacController();
	virtual void SetupInputComponent() override;

	/** Save the game */
	void SaveGame();
	/** Load the game */
	void LoadGame();
	/** Player name */
	FString MyPlayerName;
	
};

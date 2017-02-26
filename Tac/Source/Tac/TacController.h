// Copyright by GameDream.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TacVehicle.h"
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
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


	// Variable to hold the widget After Creating it.
	class UUserWidget* TacView;

	/** Save the game */
	void SaveGame();
	/** Load the game */
	void LoadGame();
	/** Clear game records */
	void EmptyGame();
	/** Player name */
	FString MyPlayerName;

private:
	TSubclassOf<class UUserWidget> PlayerView;
	
};

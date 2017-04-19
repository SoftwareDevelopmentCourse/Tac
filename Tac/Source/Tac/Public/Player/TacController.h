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
	class UGearWidget* TacView;

	/** Save the game */
	void SaveGame();
	/** Load the game */
	void LoadGame();
	/** Clear game records */
	void EmptyGame();

	void AddGearSlot();
	//UFUNCTION(Client, Reliable)
	void ClientPostLogin();
	//UFUNCTION(Client, Reliable)
	void RespawnFinished();

private:
	/** Widget blueprint's reference */
	TSubclassOf<class UUserWidget> PlayerView;
	
};

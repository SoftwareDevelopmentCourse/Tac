// Copyright by GameDream.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TacVehicle.h"
#include "TacController.generated.h"

class TacGameModeBase;
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
	UFUNCTION(Server, Reliable, WithValidation)
	void UpdateVehicle();
	UFUNCTION(Client, Reliable)
	void AddGearSlot(int32 GearIndex);
	UFUNCTION(Server, Reliable, WithValidation)
	void ClientPostLogin();
	UFUNCTION(Client, Reliable)
	void UpdateHUD();

private:
	/** Widget blueprint's reference */
	UPROPERTY()
	TSubclassOf<class UUserWidget> PlayerView;
	
};

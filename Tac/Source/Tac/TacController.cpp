// Copyright by GameDream.

#include "Tac.h"
#include "TacController.h"
#include "TacSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "TacPlayerState.h"
#include "TacVehicle.h"

ATacController::ATacController()
{
	MyPlayerName = TEXT("PlayerOne");
}

void ATacController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Save", IE_Pressed, this, &ATacController::SaveGame);
	InputComponent->BindAction("Load", IE_Pressed, this, &ATacController::LoadGame);
}

void ATacController::SaveGame()
{
	UTacSaveGame* SaveGameInstance = Cast<UTacSaveGame>(UGameplayStatics::CreateSaveGameObject(UTacSaveGame::StaticClass()));
	ATacPlayerState* TacPS = Cast<ATacPlayerState>(PlayerState);
	SaveGameInstance->PlayerName = MyPlayerName;
	SaveGameInstance->Gears = TacPS->Gears;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}

void ATacController::LoadGame()
{
	UTacSaveGame* LoadGameInstance = Cast<UTacSaveGame>(UGameplayStatics::CreateSaveGameObject(UTacSaveGame::StaticClass()));
	LoadGameInstance = Cast<UTacSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	/*
	FString PlayerNameToDisplay = LoadGameInstance->Gears[0].GetSocketName();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, PlayerNameToDisplay);
	}
	*/
	ATacVehicle* TacPawn = Cast<ATacVehicle>(GetPawn());
	TacPawn->SpawnGear(LoadGameInstance->Gears[0]);
}
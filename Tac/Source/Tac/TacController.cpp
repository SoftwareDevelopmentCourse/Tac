// Copyright by GameDream.

#include "Tac.h"
#include "TacController.h"
#include "TacSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "TacPlayerState.h"

ATacController::ATacController()
{
	MyPlayerName = TEXT("PlayerOne");

}

void ATacController::BeginPlay()
{
	Super::BeginPlay();
	LoadGame();
}

void ATacController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Save", IE_Pressed, this, &ATacController::SaveGame);
	InputComponent->BindAction("Load", IE_Pressed, this, &ATacController::LoadGame);
	InputComponent->BindAction("Empty", IE_Pressed, this, &ATacController::EmptyGame);
}

void ATacController::SaveGame()
{
	UTacSaveGame* SaveGameInstance = Cast<UTacSaveGame>(UGameplayStatics::CreateSaveGameObject(UTacSaveGame::StaticClass()));
	ATacPlayerState* TacPS = Cast<ATacPlayerState>(PlayerState);
	SaveGameInstance->PlayerName = MyPlayerName;
	SaveGameInstance->Gears = TacPS->GetGears();
	SaveGameInstance->TacTransform = TacPS->GetTacTransform();
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}

void ATacController::LoadGame()
{
	UTacSaveGame* LoadGameInstance = Cast<UTacSaveGame>(UGameplayStatics::CreateSaveGameObject(UTacSaveGame::StaticClass()));
	ATacPlayerState* TacPS = Cast<ATacPlayerState>(PlayerState);
	LoadGameInstance = Cast<UTacSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	TacPS->SetGears(LoadGameInstance->Gears);
	TacPS->SetTacTransform(LoadGameInstance->TacTransform);
}

void ATacController::EmptyGame()
{
	ATacPlayerState* TacPS = Cast<ATacPlayerState>(PlayerState);
	TacPS->EmptyGears();
	SaveGame();
}

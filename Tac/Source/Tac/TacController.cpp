// Copyright by GameDream.

#include "Tac.h"
#include "TacController.h"
#include "TacSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "TacPlayerState.h"
#include "Blueprint/UserWidget.h"

ATacController::ATacController()
{
	MyPlayerName = TEXT("PlayerOne");

	static ConstructorHelpers::FClassFinder<UUserWidget> Widget(TEXT("/Game/UMG/UMG_PlayerView"));
	if (Widget.Succeeded())
	{
		PlayerView = Widget.Class;
	}
}

void ATacController::BeginPlay()
{
	Super::BeginPlay();
	LoadGame();

	TacView = CreateWidget<UUserWidget>(this, PlayerView);
	if (TacView)
	{
		TacView->AddToViewport();
	}
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
	if (LoadGameInstance)
	{
		TacPS->SetGears(LoadGameInstance->Gears);
		TacPS->SetTacTransform(LoadGameInstance->TacTransform);
	}
	else
	{
		TacPS->EmptyGears();
		TacPS->SetTacTransform(FTransform(FTransform(FRotator(0.f, -90.f, 0.f), FVector(141.f, 0.f, 192.f), FVector(1.f))));
	}
}

void ATacController::EmptyGame()
{
	ATacPlayerState* TacPS = Cast<ATacPlayerState>(PlayerState);
	TacPS->EmptyGears();
	SaveGame();
}

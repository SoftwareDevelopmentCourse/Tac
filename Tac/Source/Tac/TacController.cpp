// Copyright by GameDream.

#include "Tac.h"
#include "TacController.h"
#include "TacSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "TacPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "TacVehicle.h"

ATacController::ATacController()
{

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
	TacPS->SetTacTransform(GetPawn()->GetActorTransform());
	SaveGameInstance->PlayerName = TacPS->GetPlayerName();
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
		TacPS->SetPlayerName(LoadGameInstance->PlayerName);
		TacPS->SetGears(LoadGameInstance->Gears);
		TacPS->SetTacTransform(LoadGameInstance->TacTransform);
	}
	else
	{
		TacPS->SetPlayerName(FString(TEXT("NULL")));
		TacPS->EmptyGears();
		TacPS->SetTacTransform(FTransform(FTransform(FRotator(0.f, -90.f, 0.f), FVector(141.f, 0.f, 192.f), FVector(1.f))));
	}
	ATacVehicle* Tac = Cast<ATacVehicle>(GetPawn());
	Tac->UpdateState();
}

void ATacController::EmptyGame()
{
	UTacSaveGame* SaveGameInstance = Cast<UTacSaveGame>(UGameplayStatics::CreateSaveGameObject(UTacSaveGame::StaticClass()));
	ATacPlayerState* TacPS = Cast<ATacPlayerState>(PlayerState);
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
	TacPS->EmptyGears();
	for (auto Actor : FoundActors)
	{
		APlayerStart* SpawnStart = Cast<APlayerStart>(Actor);
		if (!ensure(SpawnStart)) 
		{
			TacPS->SetTacTransform(FTransform());
			break; 
		}
		TacPS->SetTacTransform(SpawnStart->GetActorTransform());
		UE_LOG(LogTemp, Error, TEXT("%s"), *SpawnStart->GetName());
		break;
	}
	SaveGameInstance->PlayerName = TacPS->GetPlayerName();
	SaveGameInstance->Gears = TacPS->GetGears();
	SaveGameInstance->TacTransform = TacPS->GetTacTransform();
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}

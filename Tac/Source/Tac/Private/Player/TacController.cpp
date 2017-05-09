// Copyright by GameDream.

#include "Tac.h"
#include "TacController.h"
#include "TacSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "TacPlayerState.h"
#include "GearWidget.h"
#include "TacVehicle.h"
#include "TacGameModeBase.h"
#include "Projectile.h"
#include "GearManagementComponent.h"
#include "Engine.h"
#define OUT

ATacController::ATacController()
{
	static ConstructorHelpers::FClassFinder<UGearWidget> Widget(TEXT("/Game/Tac/Core/Characters/WBP_TacView"));
	if (Widget.Succeeded())
	{
		PlayerView = Widget.Class;
	}
	TacView = nullptr;
}

void ATacController::BeginPlay()
{
	Super::BeginPlay();
}

// Directly uses input component in controller
void ATacController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Save", IE_Pressed, this, &ATacController::SaveGame);
	InputComponent->BindAction("Load", IE_Pressed, this, &ATacController::LoadGame);
	InputComponent->BindAction("Empty", IE_Pressed, this, &ATacController::EmptyGame);
}

/*========================================================================================================
	Saving game reference: https://docs.unrealengine.com/latest/INT/Gameplay/SaveGame/Code/index.html
========================================================================================================*/
void ATacController::SaveGame()
{
	/*
	UTacSaveGame* SaveGameInstance = Cast<UTacSaveGame>(UGameplayStatics::CreateSaveGameObject(UTacSaveGame::StaticClass()));
	ATacPlayerState* TacPS = Cast<ATacPlayerState>(PlayerState);
	// Saves player's name, gears and transform
	SaveGameInstance->PlayerName = TacPS->GetPlayerName();
	SaveGameInstance->Gears = TacPS->GetGears();
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
	*/

}

void ATacController::LoadGame()
{
	/*
		UTacSaveGame* LoadGameInstance = Cast<UTacSaveGame>(UGameplayStatics::CreateSaveGameObject(UTacSaveGame::StaticClass()));
	ATacPlayerState* TacPS = Cast<ATacPlayerState>(PlayerState);
	if (!ensure(TacPS)) { return; }
	LoadGameInstance = Cast<UTacSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	if (LoadGameInstance) // Could load from the previous GameInstance
	{
		TacPS->SetPlayerName(LoadGameInstance->PlayerName);
		TacPS->SetGears(LoadGameInstance->Gears);
	}
	else // If there's no GameInstance exists
	{
		TacPS->SetPlayerName(FString(TEXT("NULL")));
		TacPS->EmptyGears();
	}
	*/

}

void ATacController::EmptyGame()
{
	/*
		UTacSaveGame* SaveGameInstance = Cast<UTacSaveGame>(UGameplayStatics::CreateSaveGameObject(UTacSaveGame::StaticClass()));
	ATacPlayerState* TacPS = Cast<ATacPlayerState>(PlayerState);
	// Reset player respawn location at PlayerStart
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
	// Empty player state and save to GameInstance
	TacPS->SetName(TEXT("DEFAULT"));
	TacPS->EmptyGears();
	ATacVehicle* Tac = Cast<ATacVehicle>(GetPawn());
	UGearManagementComponent* Manager = Cast<UGearManagementComponent>(Tac->GetGearManager());
	Manager->ResetGears();
	SaveGameInstance->PlayerName = TacPS->GetPlayerName();
	SaveGameInstance->Gears = TacPS->GetGears();
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
	*/
}

bool ATacController::UpdateVehicle_Validate()
{
	return true;
}

void ATacController::UpdateVehicle_Implementation()
{
	ATacVehicle* Tac = Cast<ATacVehicle>(GetPawn());
	// Spawns gears which player already had
	Tac->UpdateState();
}

void ATacController::AddGearSlot_Implementation(int32 GearIndex)
{
	if (!IsLocalController())
	{
		UE_LOG(LogTemp, Error, TEXT("Is not local controller"));
		return;
	}
	TacView->AddGearSlot(GearIndex);
}

bool ATacController::ClientPostLogin_Validate()
{
	return true;
}

void ATacController::ClientPostLogin_Implementation()
{
	if (HasAuthority())
	{
		if (!ensure(PlayerState))
		{
			UE_LOG(LogTemp, Error, TEXT("No playerstate"));
			return;
		}
		//LoadGame();
		ATacPlayerState* TacPS = Cast<ATacPlayerState>(PlayerState);
		TacPS->EmptyGears();
		AGameModeBase* CurrentGameMode = GetWorld()->GetAuthGameMode();
		if (!ensure(CurrentGameMode))
		{
			UE_LOG(LogTemp, Error, TEXT("No gamemode"));
			return;
		}
		ATacGameModeBase* TacGameMode = Cast<ATacGameModeBase>(CurrentGameMode);
		TacGameMode->RespawnPlayerEvent(this);
		UE_LOG(LogTemp, Error, TEXT("Server"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Client"));
	}
}

void ATacController::UpdateHUD_Implementation()
{
	if (!IsLocalController())
	{
		UE_LOG(LogTemp, Error, TEXT("Is not local controller"));
		return;
	}
	TacView = CreateWidget<UGearWidget>(this, PlayerView);
	if (TacView)
	{
		TacView->AddToViewport();
	}
}

FVector ATacController::Aimat(FVector StartLoc, float LaunchVelocity)
{
	FVector OutLaunchVelocity;
	FVector HitLocation;
	GetSightRayHitLocation(HitLocation);
	auto AimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLoc,
		HitLocation,
		LaunchVelocity,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace);
	return OutLaunchVelocity.GetSafeNormal();
}


bool ATacController::GetSightRayHitLocation(FVector& HitLocation) const
{
	if (!IsLocalController()) { return false; }
	int32 ScreenX, ScreenY;
	FVector2D ViewportSize;
	GetViewportSize(ScreenX, ScreenY);
	auto ScreenLocation = FVector2D(ScreenX * CrosshairXLocation, ScreenY * CrosshairYLocation);
	FVector WorldDirection;
	UE_LOG(LogTemp, Error, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());
	if (GetLookDirection(ScreenLocation, WorldDirection))
	{
		return GetLookHitLocation(WorldDirection, HitLocation);
	}
	return false;
}

bool ATacController::GetLookDirection(FVector2D ScreenLocation, FVector& WorldDirection) const
{
	FVector WorldLocation;
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection);
	UE_LOG(LogTemp, Error, TEXT("Result: %i\tScreenToWorld location: %s"), *WorldDirection.ToString());
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection);
}

bool ATacController::GetLookHitLocation(FVector WorldDirection, FVector& HitLocation) const
{
	FHitResult Hit;
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);
	if (GetWorld()->LineTraceSingleByChannel(
		Hit,
		CameraLocation,
		CameraLocation + WorldDirection * LineTraceRange,
		ECollisionChannel::ECC_Camera)
		)
	{
		HitLocation = Hit.Location;
		return true;
	}
	HitLocation = FVector(0.f);
	return false;
}
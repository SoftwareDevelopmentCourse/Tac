// Copyright by GameDream.

#include "Tac.h"
#include "TacGameModeBase.h"
#include "GearSpawnVolume.h"
#include "TacController.h"
#include "TacPlayerState.h"
#include "UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

ATacGameModeBase::ATacGameModeBase()
{
	/*============================================
		Initialize for the Pawn and Controller
	============================================*/
	/*
	static ConstructorHelpers::FClassFinder<APawn> TacPawnBP(TEXT("/Game/Tac/Core/Characters/BP_Tac"));
	if (!ensure(TacPawnBP.Succeeded())) { return; }
	DefaultPawnClass = TacPawnBP.Class;
	*/
	
	static ConstructorHelpers::FClassFinder<AController> TacController(TEXT("Class'/Script/Tac.TacController'"));
	if (!ensure(TacController.Succeeded())) { return; }
	PlayerControllerClass = TacController.Class;
}

void ATacGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	/*================================
		Spawn all GearSpawnVolumes
	================================*/
	ActiveGearVolume();
	InitSpawnStart();
}

void ATacGameModeBase::PostLogin(APlayerController* NewController)
{
	Super::PostLogin(NewController);
	if (HasAuthority())
	{
		ATacPlayerState* NewTacPlayerState = Cast<ATacPlayerState>(NewController->PlayerState);
		NewTacPlayerState->PlayerNumber = GameState->PlayerArray.Num();
		ATacController* NewTacController = Cast<ATacController>(NewController);
		NewTacController->ClientPostLogin();
		NewTacController->UpdateHUD();
	}
}

void ATacGameModeBase::RespawnPlayerEvent(AController * PlayerController)
{
	if (PlayerController->GetPawn())
	{
		PlayerController->GetPawn()->Destroy();
	}
	ATacPlayerState* TacPlayerState = Cast<ATacPlayerState>(PlayerController->PlayerState);
	FTransform SpawnTransform;
	if (TacPlayerState->bIsGroup_A)
	{
		if (!ensure(SpawnStart_A.IsValidIndex(0)))
		{
			UE_LOG(LogTemp, Error, TEXT("No PlayerStart_A for Group_A"));
			return;
		}
		SpawnTransform = SpawnStart_A[0]->GetActorTransform();
	}
	else
	{
		if (!ensure(SpawnStart_B.IsValidIndex(0)))
		{
			UE_LOG(LogTemp, Error, TEXT("No PlayerStart_B for Group_B"));
			return;
		}
		int32 StartIndex = FMath::RandRange(0, SpawnStart_B.Num() - 1);
		SpawnTransform = SpawnStart_B[StartIndex]->GetActorTransform();
		SpawnStart_B.RemoveAt(StartIndex);
	}
	ATacVehicle* NewTac = GetWorld()->SpawnActor<ATacVehicle>(ATacVehicle::StaticClass(), SpawnTransform);// TODO spawn BP
	PlayerController->Possess(NewTac);
	ATacController* TacController = Cast<ATacController>(PlayerController);
	TacController->UpdateVehicle();
}

void ATacGameModeBase::ActiveGearVolume()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGearSpawnVolume::StaticClass(), FoundActors);
	for (auto Actor : FoundActors)
	{
		AGearSpawnVolume* SpawnVolumeActor = Cast<AGearSpawnVolume>(Actor);
		if (!ensure(SpawnVolumeActor)) { return; }
		SpawnVolumeActor->SpawnActors();
	}
}

void ATacGameModeBase::InitSpawnStart()
{
	if (!ensure(GetWorld())) { return; }
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
	for (auto Actor : FoundActors)
	{
		APlayerStart* PlayerStartActor = Cast<APlayerStart>(Actor);
		if (!ensure(PlayerStartActor)) { return; }
		if (PlayerStartActor->PlayerStartTag == TEXT("PlayerA"))
		{
			SpawnStart_A.AddUnique(PlayerStartActor);
		}
		else if (PlayerStartActor->PlayerStartTag == TEXT("PlayerB"))
		{
			SpawnStart_B.AddUnique(PlayerStartActor);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Has Player start B : %i"), SpawnStart_B.Num());
}
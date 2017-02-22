// Copyright by GameDream.

#include "Tac.h"
#include "TacGameModeBase.h"
#include "GearSpawnVolume.h"
#include "Kismet/GameplayStatics.h"

ATacGameModeBase::ATacGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> TacPawnBP(TEXT("/Game/Tac/MyTacVehicle"));
	if (!ensure(TacPawnBP.Succeeded())) { return; }
	DefaultPawnClass = TacPawnBP.Class;
	static ConstructorHelpers::FClassFinder<AController> TacController(TEXT("Class'/Script/Tac.TacController'"));
	if (!ensure(TacController.Succeeded())) { return; }
	PlayerControllerClass = TacController.Class;
}

void ATacGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGearSpawnVolume::StaticClass(), FoundActors);
	for (auto Actor : FoundActors)
	{
		AGearSpawnVolume* SpawnVolumeActor = Cast<AGearSpawnVolume>(Actor);
		if (!ensure(SpawnVolumeActor)) { return; }
		SpawnVolumeActor->SpawnActors();
	}
}
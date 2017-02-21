// Copyright by GameDream.

#include "Tac.h"
#include "TacGameModeBase.h"
#include "GearSpawnVolume.h"
#include "Kismet/GameplayStatics.h"

ATacGameModeBase::ATacGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> TacBP(TEXT("/Game/Tac/MyTacVehicle"));
	DefaultPawnClass = TacBP.Class;

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
		UE_LOG(LogTemp, Log, TEXT("%s"), *Actor->GetName());
	}
}
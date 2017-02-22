// Copyright by GameDream.

#include "Tac.h"
#include "GearSpawnVolume.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGearSpawnVolume::AGearSpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = SpawnVolume;
}

// Called when the game starts or when spawned
void AGearSpawnVolume::BeginPlay()
{
	Super::BeginPlay();

}

FVector AGearSpawnVolume::GetRandomPointInVolume()
{
	auto SpawnOrigin = SpawnVolume->Bounds.Origin;
	auto SpawnExtent = SpawnVolume->Bounds.BoxExtent;
	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void AGearSpawnVolume::SpawnActors()
{
	auto World = GetWorld();
	if (!ensure(World)) { return; }
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;
	for (auto Spawn : SpawnStructs)
	{
		for (int32 iSpawn = 0; iSpawn < Spawn.GetSpawnAmount(); iSpawn++)
		{
			auto SpawnLocation = GetRandomPointInVolume();
			auto SpawnRotation = FRotator(0.f, FMath::FRand() * 360.f, 0.f);
			World->SpawnActor<AActor>(Spawn.GetSpawnActor(), SpawnLocation, SpawnRotation, SpawnParams);
		}
	}
}


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
	if (!ensure(WhatToSpawn.IsValidIndex(0))) { return; }
	for (auto Spawn : WhatToSpawn)
	{
		auto World = GetWorld();
		if (!ensure(World)) { return; }
		auto SpawnLocation = GetRandomPointInVolume();
		auto SpawnRotation = FRotator(FMath::FRand() * 360.f, FMath::FRand() * 360.f, FMath::FRand() * 360.f);
		World->SpawnActor<AActor>(Spawn, SpawnLocation, SpawnRotation);
		UE_LOG(LogTemp, Log, TEXT("%s"), *Spawn->GetName());
	}
}

FVector AGearSpawnVolume::GetRandomPointInVolume()
{
	auto SpawnOrigin = SpawnVolume->Bounds.Origin;
	auto SpawnExtent = SpawnVolume->Bounds.BoxExtent;
	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void AGearSpawnVolume::SpawnActors()
{
	if (!ensure(WhatToSpawn.IsValidIndex(0))) { return; }
	for (auto Spawn : WhatToSpawn)
	{
		auto World = GetWorld();
		if (!ensure(World)) { return; }
		auto SpawnLocation = GetRandomPointInVolume();
		auto SpawnRotation = FRotator(FMath::FRand() * 360.f, FMath::FRand() * 360.f, FMath::FRand() * 360.f);
		World->SpawnActor<AActor>(Spawn, SpawnLocation, SpawnRotation);
		UE_LOG(LogTemp, Log, TEXT("%s"), *Spawn->GetName());
	}
}


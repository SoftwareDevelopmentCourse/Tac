// Copyright by GameDream.

#pragma once

#include "GameFramework/Actor.h"
#include "GearSpawnVolume.generated.h"

USTRUCT()
struct FGearSpawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> WhatToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 SpawnAmount;

	TSubclassOf<AActor> GetSpawnActor()
	{
		return WhatToSpawn;
	}

	int32 GetSpawnAmount()
	{
		return SpawnAmount;
	}

	FGearSpawn()
	{
		WhatToSpawn = NULL;
		SpawnAmount = 1;
	}
};

UCLASS()
class TAC_API AGearSpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGearSpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(Category = Spawning, EditAnywhere, BlueprintReadOnly)
	TArray<FGearSpawn> SpawnStructs;
	UPROPERTY(Category = Spawning, VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* SpawnVolume;
	
	UFUNCTION(Category = Spawning, BlueprintCallable)
	void SpawnActors();

private:
	FVector GetRandomPointInVolume();
};

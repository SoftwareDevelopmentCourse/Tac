// Copyright by GameDream.

#pragma once

#include "GameFramework/Actor.h"
#include "GearSpawnVolume.generated.h"

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
	TArray<TSubclassOf<AActor>> WhatToSpawn;
	UPROPERTY(Category = Spawning, VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* SpawnVolume;
	
	UFUNCTION(Category = Spawning, BlueprintCallable)
	void SpawnActors();

private:
	FVector GetRandomPointInVolume();
};

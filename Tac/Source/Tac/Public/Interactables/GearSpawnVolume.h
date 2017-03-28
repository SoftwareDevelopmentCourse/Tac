// Copyright by GameDream.

#pragma once

#include "GameFramework/Actor.h"
#include "TacHeader.h"
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
	/** Gear spawning type and amount */
	UPROPERTY(Category = Spawning, EditAnywhere, BlueprintReadOnly)
	TArray<FGearSpawn> SpawnStructs;
	/** Spawning box volume component */
	UPROPERTY(Category = Spawning, VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* SpawnVolume;
	/** Spawning function */
	UFUNCTION(Category = Spawning, BlueprintCallable)
	void SpawnActors();

private:
	/** Function of generating random point to spawn */
	FVector GetRandomPointInVolume();
};

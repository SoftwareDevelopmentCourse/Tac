// Copyright by GameDream.
#pragma once

#include "GameFramework/GameModeBase.h"
#include "TacGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TAC_API ATacGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATacGameModeBase();

	virtual void BeginPlay() override;

private:
	/** Volumes that spawns gears */
	TArray<class AGearSpawnVolume*> SpawnVolumeActors;
};

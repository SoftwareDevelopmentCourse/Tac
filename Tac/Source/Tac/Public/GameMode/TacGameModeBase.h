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
	
	virtual void PostLogin(APlayerController* NewPlayer) override;

	TArray<APlayerStart*> SpawnStart_A;
	TArray<APlayerStart*> SpawnStart_B;
	void RespawnPlayerEvent(AController* PlayerController);

private:
	/** Volumes that spawns gears */
	TArray<class AGearSpawnVolume*> SpawnVolumeActors;

	void ActiveGearVolume();
	void InitSpawnStart();
	int32 PlayerIndex;
};

// Copyright by GameDream.

#pragma once

#include "GameFramework/PlayerState.h"
#include "TacHeader.h"
#include "TacPlayerState.generated.h"

class AGears;
class ATacVehicle;
/**
 * 
 */
UCLASS()
class TAC_API ATacPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ATacPlayerState();
	/** Functions for reading data */
	UFUNCTION(BlueprintPure, Category = State)
	TArray<TSubclassOf<AGears>> GetGears();
	UFUNCTION(BlueprintPure, Category = State)
	TSubclassOf<AGears> GetGear(int32 GearIndex);
	UFUNCTION(BlueprintPure, Category = State)
	FString GetSocketName(int32 GearIndex);
	UFUNCTION(BlueprintPure, Category = State)
	FString GetPlayerName();
	UFUNCTION(BlueprintPure, Category = State)
	FName GetGearName(int32 GearIndex);

	/** Functions for writing data */
	UFUNCTION(BlueprintCallable, Category = State)
	void SetGears(TArray<TSubclassOf<AGears>> GearsToSet);
	UFUNCTION(BlueprintCallable, Category = State)
	void AddGear(int32 GearIndex, TSubclassOf<AGears> GearToAdd);
	UFUNCTION(BlueprintCallable, Category = State)
	void EmptyGears();
	UFUNCTION(BlueprintCallable, Category = State)
	void SetName(FString NameToSet);

private:
	/*==========================================
		Saves player state for synchronizing	
	==========================================*/
	UPROPERTY(Replicated)
	TArray<TSubclassOf<AGears>> Gears;
	FString MyPlayerName = TEXT("Tacky");
	int32 GearsAmount;
	
public:
	int32 PlayerNumber;
	bool bIsGroup_A;
};

// Copyright by GameDream.

#pragma once

#include "GameFramework/PlayerState.h"
#include "TacVehicle.h"
#include "TacPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TAC_API ATacPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, Category = State)
	TArray<FGear> GetGears();
	UFUNCTION(BlueprintPure, Category = State)
	FGear GetGear(int32 GearIndex);
	UFUNCTION(BlueprintCallable, Category = State)
	void SetGears(TArray<FGear> GearsToSet);
	UFUNCTION(BlueprintCallable, Category = State)
	void AddGear(FGear GearToAdd);
	UFUNCTION(BlueprintCallable, Category = State)
	void EmptyGears();
	UFUNCTION(BlueprintPure, Category = State)
	FTransform GetTacTransform();
	UFUNCTION(BlueprintCallable, Category = State)
	void SetTacTransform(FTransform TransformToSet);
	UFUNCTION(BlueprintPure, Category = State)
	FString GetPlayerName();
	UFUNCTION(BlueprintCallable, Category = State)
	void SetName(FString NameToSet);

private:
	TArray<FGear> Gears;
	FTransform TacTransform;
	FString MyPlayerName = TEXT("Tacky");
	
};

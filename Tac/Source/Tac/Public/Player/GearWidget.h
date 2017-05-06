// Copyright by GameDream.

#pragma once

#include "Blueprint/UserWidget.h"
#include "GearWidget.generated.h"

/**
 * 
 */
UCLASS()
class TAC_API UGearWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//UGearWidget();
	UFUNCTION(BlueprintImplementableEvent, Category = "Gear")
	void AddGearSlot(int32 GearIndex);
	UFUNCTION(BlueprintImplementableEvent, Category = "State")
	void InitializePlayerState();

};

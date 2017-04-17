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
	UFUNCTION(BlueprintImplementableEvent, Category = "Gear")
	void AddGearSlot();
	
	
};

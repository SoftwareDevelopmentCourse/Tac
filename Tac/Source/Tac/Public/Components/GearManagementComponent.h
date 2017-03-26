// Copyright by GameDream.

#pragma once

#include "Components/ActorComponent.h"
#include "TacHeader.h"
#include "GearManagementComponent.generated.h"

class ATacVehicle;
class ATacPlayerState;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TAC_API UGearManagementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGearManagementComponent();
	
	ATacVehicle* OwnerVehicle;
	ATacPlayerState* OwnerPS;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	/** Called every frame */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/** Spawn gear to tac */
	void SpawnGear(FGear GearToSet);
	/** Update tac state */
	void UpdateData(FGear GearToAdd);
	/** Try to add gear to vehicle */
	void TryAddGear(FGear GearToAdd);
	
public:
	/*============================
		Bind axis and action
	============================*/
	/** When mouse looking up */
	void OnLookUp(float val);
	/** When mouse looking right */
	void OnLookRight(float val);
	
	/** When hitting spacebar */
	void OnSpaceHit();
	/** When hitting left shift */
	void OnShiftHit();
	/** When hitting key Q */
	void OnKeyQHit();

private:
	TArray<FGear> OwnedGears;
};

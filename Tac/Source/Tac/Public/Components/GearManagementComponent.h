// Copyright by GameDream.

#pragma once

#include "Components/ActorComponent.h"
#include "TacHeader.h"
#include "GearManagementComponent.generated.h"

class ATacVehicle;
class ATacPlayerState;
class UGearComponent;
class AGears;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TAC_API UGearManagementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGearManagementComponent();
	
	/** Sets owner's properties for component's use */
	ATacVehicle* OwnerVehicle;
	ATacPlayerState* OwnerPS;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	/** Called every frame */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/** Spawn gear to tac */
	void SpawnGear(TSubclassOf<AGears> GearToSpawn);
	/** Update player's gears state and locall gears state */
	void UpdateData(TSubclassOf<AGears> GearToAdd);
	/** Try to add gear to vehicle when picking up gears */
	void TryAddGear(TSubclassOf<AGears> GearToAdd);
	
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

	/** When hitting left mouse button */
	void OnLClickHit();

	/** When hitting right mouse button */
	void OnRClickHit();

private:
	/*==============================================
		Private variables for component's use
	==============================================*/
	TArray<AGears*> OwnedGears;
	/** For judging by gear type */
	bool bShiftBind;
	bool bSpaceBind;
	bool bKeyQBind;
	bool bLClickBind;
	bool bRClickBind;
	bool bMouseBind;
	/** For judging by gear socket */
	bool bHasFront;
	bool bHasBack;
	bool bHasLeft;
	bool bHasRight;

private:
	/** Judge by gear socket */
	void JudgeBySocket(AGears* GearToJudge);
	/** Judge by gear type */
	void JudgeByType(AGears* GearToJudge);
};

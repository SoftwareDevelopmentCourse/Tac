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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	/** Called every frame */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/** Try to pick up gear */
	UFUNCTION(Server, Reliable, WithValidation)
	void TryPickup(AGears* GearToPickup);
	/** Reset tac gears as class AGears */
	void ResetGears();
	
public:
	/*============================
		Bind axis and action
	============================*/
	/** When mouse looking up */
	UFUNCTION(Server, Reliable, WithValidation)
	void OnLookUp(float val);

	/** When mouse looking right */
	UFUNCTION(Server, Reliable, WithValidation)
	void OnLookRight(float val);
	
	/** When hitting spacebar */
	UFUNCTION(Server, Reliable, WithValidation)
	void OnSpaceHit();

	/** When hitting left shift */
	UFUNCTION(Server, Reliable, WithValidation)
	void OnShiftHit();

	/** When hitting key Q */
	UFUNCTION(Server, Reliable, WithValidation)
	void OnKeyQHit();

	/** When hitting left mouse button */
	UFUNCTION(Server, Reliable, WithValidation)
	void OnLClickHit();

	/** When hitting right mouse button */
	UFUNCTION(Server, Reliable, WithValidation)
	void OnRClickHit();

private:
	/*==============================================
		Private variables for component's use
	==============================================*/
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
	void JudgeBySocket(AGears* GearToJudge, int32 & Result);
	/** Initialize gear's boolean states */
	void InitializeState();

	void BindKey(AGears * GearToBind);
	/** Storages every socket's gear */
	UPROPERTY(Replicated)
	TArray<AActor*> TacGears;

};

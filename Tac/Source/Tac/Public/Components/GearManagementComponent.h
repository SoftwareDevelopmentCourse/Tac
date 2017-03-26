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
	
	ATacVehicle* OwnerVehicle;
	ATacPlayerState* OwnerPS;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	/** Called every frame */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/** Spawn gear to tac */
	void SpawnGear(TSubclassOf<AGears> GearToSet);
	/** Update tac state */
	void UpdateData(TSubclassOf<AGears> GearToAdd);
	/** Try to add gear to vehicle */
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

private:
	TArray<TSubclassOf<AGears>> OwnedGears;

	bool bShiftBind;
	bool bSpaceBind;
	bool bKeyQBind;
	bool bLClickBind;
	bool bRClickBind;
	bool bMouseBind;

	bool bHasFront;
	bool bHasBack;
	bool bHasLeft;
	bool bHasRight;

private:
	void JudgeSocket(AGears* GearToJudge);
	void JudgeType(AGears* GearToJudge);
};

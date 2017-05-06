// Copyright by GameDream.

#pragma once

#include "WheeledVehicle.h"
#include "TacVehicle.generated.h"

/**
 * Actor one, main pawn, good luck!
 */

class UCameraComponent;
class USpringArmComponent;
class UInputComponent;
class UPickupComponent;
class UDamageComponent;
class UGearManagementComponent;

UCLASS()
class TAC_API ATacVehicle : public AWheeledVehicle
{
	GENERATED_BODY()

	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	/** Pickup component deals with interations between Tac and world */
	UPROPERTY(Category = Gear, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPickupComponent* PickupVolume;
	
	/** Gear manager to manage gears */
	UPROPERTY(Category = Gear, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UGearManagementComponent* GearManager;

	// Damage manager deals with player's health and armor
	UPROPERTY(Category = Gear, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDamageComponent* DamageManager;

public:
	ATacVehicle(const FObjectInitializer& ObjectInitializer);
	
	/*===========================
		Tac's using component
	===========================*/
	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* PickupCapsule;

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

	/** Handle pressing forwards */
	void MoveForward(float val);
	/** Handle pressing right */
	void MoveRight(float val);
	/** Rotate Camera to adjust the view */
	void RotateCamera(float val);
	/** Lift Camera to adjust the view */
	void LiftCamera(float val);
	/** Zoom camera to adjust the view */
	void ZoomCamera(float val);
	/** Pick up surrounding gear */
	void PickupGear();

public:

	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
	FORCEINLINE UGearManagementComponent* GetGearManager() const { return GearManager; }
	FORCEINLINE UDamageComponent* GetDamageManager() const { return DamageManager; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float BoostSpeed;
	/** Called from player controller to update tac's state */
	void UpdateState();

};

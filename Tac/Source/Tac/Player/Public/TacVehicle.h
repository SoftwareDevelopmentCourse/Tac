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
class UCapsuleComponent;
class UEjectorComponent;

UENUM(BlueprintType)
enum class EGearSocket : uint8
{
	ENull,
	ELeft,
	ERight,
	EBack
};

USTRUCT()
struct FGear
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gear)
	TSubclassOf<UStaticMeshComponent> Gear;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gear)
	EGearSocket Socket;
	FString GetSocketName()
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGearSocket"), true);
		if (!EnumPtr) return FString("Invalid");
		return EnumPtr->GetEnumName((int32)Socket);
	}

	FGear()
	{
		Gear = NULL;
		Socket = EGearSocket::EBack;
	}

};

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

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CollectCapsule;

	
public:
	ATacVehicle(const FObjectInitializer& ObjectInitializer);
	
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
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
	/** Boost the vehicle */
	void Boost();
	/** Handle handbrake pressed */
	void OnHandbrakePressed();
	/** Handle handbrake released */
	void OnHandbrakeReleased();
	/** Try to pick up ejector and take it */
	void GetEjector();


public:
	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float BoostSpeed;

	void SpawnGear(FGear GearToSet);
	void AddToState(FGear GearToAdd);
	void UpdateState();
};
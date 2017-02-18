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
	
public:
	ATacVehicle();
	
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	void MoveForward(float val);

	void MoveRight(float val);

	void RotateCamera(float val);

	void Boost();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float BoostSpeed;

public:
	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
};

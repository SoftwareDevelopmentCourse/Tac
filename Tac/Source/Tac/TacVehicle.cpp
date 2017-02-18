// Copyright by GameDream.

#include "Tac.h"
#include "TacVehicle.h"
#include "VehicleWheel.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "WheeledVehicleMovementComponent4W.h"
#include "Engine/SkeletalMesh.h"

ATacVehicle::ATacVehicle()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> TacMesh(TEXT("/Game/Tac/SK_Tac"));
	GetMesh()->SetSkeletalMesh(TacMesh.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> TacAnim(TEXT("/Game/Tac/AnimBP_TacPawn"));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetAnimInstanceClass(TacAnim.Class);

	UWheeledVehicleMovementComponent4W* Vehicle4W = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovement());

	check(Vehicle4W->WheelSetups.Num() == 4);

	static ConstructorHelpers::FClassFinder<UVehicleWheel> FrontWheel(TEXT("/Game/Tac/BP_TacWheel_Front"));
	static ConstructorHelpers::FClassFinder<UVehicleWheel> RearWheel(TEXT("/Game/Tac/BP_TacWheel_Rear"));

	Vehicle4W->WheelSetups[0].WheelClass = FrontWheel.Class;
	Vehicle4W->WheelSetups[0].BoneName = FName("PhysWheel_FL");
	Vehicle4W->WheelSetups[0].AdditionalOffset = FVector(0.f, -20.f, 0.f);

	Vehicle4W->WheelSetups[1].WheelClass = FrontWheel.Class;
	Vehicle4W->WheelSetups[1].BoneName = FName("PhysWheel_FR");
	Vehicle4W->WheelSetups[1].AdditionalOffset = FVector(0.f, -20.f, 0.f);

	Vehicle4W->WheelSetups[2].WheelClass = RearWheel.Class;
	Vehicle4W->WheelSetups[2].BoneName = FName("PhysWheel_BL");
	Vehicle4W->WheelSetups[2].AdditionalOffset = FVector(0.f, -20.f, 0.f);

	Vehicle4W->WheelSetups[3].WheelClass = RearWheel.Class;
	Vehicle4W->WheelSetups[3].BoneName = FName("PhysWheel_BR");
	Vehicle4W->WheelSetups[3].AdditionalOffset = FVector(0.f, -20.f, 0.f);

	Vehicle4W->Mass = 1000.f;
	Vehicle4W->EngineSetup.MOI = 0.5f;
	Vehicle4W->DifferentialSetup.DifferentialType = EVehicleDifferential4W::LimitedSlip_4W;

	// Create a spring arm component for our chase camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetRelativeLocation(FVector(80.0f, 0.0f, 108.0f));
	SpringArm->SetWorldRotation(FRotator(-15.0f, 0.0f, 0.0f));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 250.0f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->bEnableCameraRotationLag = false;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;

	// Create the chase camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ChaseCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->SetRelativeLocation(FVector(-125.0, 0.0f, 0.0f));
	Camera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	Camera->bUsePawnControlRotation = false;
	Camera->FieldOfView = 90.f;

	BoostSpeed = 400.f;
}

void ATacVehicle::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATacVehicle::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATacVehicle::MoveRight);
	PlayerInputComponent->BindAxis("LookRight", this, &ATacVehicle::RotateCamera);

	PlayerInputComponent->BindAction("Boost", IE_Pressed, this, &ATacVehicle::Boost);

}

void ATacVehicle::MoveForward(float Val)
{
	GetVehicleMovementComponent()->SetThrottleInput(Val);

}

void ATacVehicle::MoveRight(float Val)
{
	GetVehicleMovementComponent()->SetSteeringInput(Val);
}

void ATacVehicle::RotateCamera(float val)
{
	SpringArm->AddRelativeRotation(FRotator(0.f, val, 0.f));
}

void ATacVehicle::Boost()
{
	auto Boost = GetMesh()->GetForwardVector() * BoostSpeed;
	/*
	auto CurrentVelocity = GetMesh()->GetPhysicsLinearVelocity();
	GetMesh()->SetPhysicsLinearVelocity(CurrentVelocity + Boost);
	*/
	GetMesh()->AddImpulse(Boost,NAME_None,true);
	UE_LOG(LogTemp, Error, TEXT("%s"), *Boost.ToString());
}
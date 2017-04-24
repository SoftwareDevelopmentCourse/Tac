// Copyright by GameDream.

#include "Tac.h"
#include "TacVehicle.h"
#include "VehicleWheel.h"
#include "Engine/SkeletalMesh.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TacHeader.h"
#include "Gears.h"
#include "TacPlayerState.h"
#include "DamageComponent.h"
#include "PickupComponent.h"
#include "GearManagementComponent.h"
#include "Components/TacMovementComponent4W.h"

ATacVehicle::ATacVehicle(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UTacMovementComponent4W>(VehicleMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;
	/*=======================================================================================================
		Initialize Tac's mesh, ainmation, movement component, camera, pickup component and gear component
	=======================================================================================================*/
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> TacMesh(TEXT("SkeletalMesh'/Game/Tac/Characters/SK_Tac.SK_Tac'"));
	if (TacMesh.Object)
	{
		GetMesh()->SetSkeletalMesh(TacMesh.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> TacAnim(TEXT("/Game/Tac/Core/Characters/ABP_TacPawn"));
	if (TacAnim.Class)
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(TacAnim.Class);
	}

	UTacMovementComponent4W* Vehicle4W = CastChecked<UTacMovementComponent4W>(GetVehicleMovement());

	check(Vehicle4W->WheelSetups.Num() == 4); // Vehicle wheel's amount needs to be 4 when using WheeledVehicleMovementComponent

	static ConstructorHelpers::FClassFinder<UVehicleWheel> FrontWheel(TEXT("/Game/Tac/Core/Characters/BP_TacWheel_Front"));
	static ConstructorHelpers::FClassFinder<UVehicleWheel> RearWheel(TEXT("/Game/Tac/Core/Characters/BP_TacWheel_Rear"));
	if (FrontWheel.Class && RearWheel.Class)
	{
		Vehicle4W->WheelSetups[0].WheelClass = FrontWheel.Class;
		Vehicle4W->WheelSetups[0].BoneName = FName("PhysWheel_FL");
		Vehicle4W->WheelSetups[0].AdditionalOffset = FVector(0.f, -20.f, 0.f);

		Vehicle4W->WheelSetups[1].WheelClass = FrontWheel.Class;
		Vehicle4W->WheelSetups[1].BoneName = FName("PhysWheel_FR");
		Vehicle4W->WheelSetups[1].AdditionalOffset = FVector(0.f, 20.f, 0.f);

		Vehicle4W->WheelSetups[2].WheelClass = RearWheel.Class;
		Vehicle4W->WheelSetups[2].BoneName = FName("PhysWheel_BL");
		Vehicle4W->WheelSetups[2].AdditionalOffset = FVector(0.f, -20.f, 0.f);

		Vehicle4W->WheelSetups[3].WheelClass = RearWheel.Class;
		Vehicle4W->WheelSetups[3].BoneName = FName("PhysWheel_BR");
		Vehicle4W->WheelSetups[3].AdditionalOffset = FVector(0.f, 20.f, 0.f);

		Vehicle4W->Mass = 1000.f;
		Vehicle4W->EngineSetup.MOI = 0.5f;
		Vehicle4W->DifferentialSetup.DifferentialType = EVehicleDifferential4W::LimitedSlip_4W;
	}

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
	SpringArm->bInheritRoll = false;

	// Create the chase camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ChaseCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->SetRelativeLocation(FVector(-125.0, 0.0f, 0.0f));
	Camera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	Camera->bUsePawnControlRotation = false;
	Camera->FieldOfView = 90.f;

	// Create the pickup capsule
	PickupCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PickupCapsule"));
	PickupCapsule->SetupAttachment(RootComponent);
	PickupCapsule->SetCapsuleHalfHeight(750.f);
	PickupCapsule->SetCapsuleRadius(350.f);
	PickupCapsule->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));

	// Create the gear management component
	GearManager = CreateDefaultSubobject<UGearManagementComponent>(TEXT("GearManager"));

	// Create the damage component
	DamageManager = CreateDefaultSubobject<UDamageComponent>(TEXT("DamageManager"));
	DamageManager->SetIsReplicated(true);

	// Create the pickup component
	PickupVolume = CreateDefaultSubobject<UPickupComponent>(TEXT("PickupVolume"));
	BoostSpeed = 400.f;

	// Initialization for ChildActorComponent
	// Reference: https://forums.unrealengine.com/showthread.php?53823-c-equivalent-of-Add-ChildActorComponent
	GearActorFront = CreateDefaultSubobject<UChildActorComponent>(TEXT("GearFront"));
	GearActorFront->SetupAttachment(RootComponent, TEXT("EFront"));

	GearActorBack = CreateDefaultSubobject<UChildActorComponent>(TEXT("GearBack"));
	GearActorBack->SetupAttachment(RootComponent, TEXT("EBack"));

	GearActorLeft = CreateDefaultSubobject<UChildActorComponent>(TEXT("GearLeft"));
	GearActorLeft->SetupAttachment(RootComponent, TEXT("ELeft"));

	GearActorRight = CreateDefaultSubobject<UChildActorComponent>(TEXT("GearRight"));
	GearActorRight->SetupAttachment(RootComponent, TEXT("ERight"));
}

void ATacVehicle::BeginPlay()
{
	Super::BeginPlay();

}

void ATacVehicle::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATacVehicle::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATacVehicle::MoveRight);
	PlayerInputComponent->BindAxis("LookRight", this, &ATacVehicle::RotateCamera);
	PlayerInputComponent->BindAxis("LookUp", this, &ATacVehicle::LiftCamera);
	PlayerInputComponent->BindAxis("Zoom", this, &ATacVehicle::ZoomCamera);
	PlayerInputComponent->BindAxis("LookUp", GearManager, &UGearManagementComponent::OnLookUp);
	PlayerInputComponent->BindAxis("LookRight", GearManager, &UGearManagementComponent::OnLookRight);

	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &ATacVehicle::PickupGear);
	PlayerInputComponent->BindAction("LClick", IE_Pressed, GearManager, &UGearManagementComponent::OnLClickHit);
	PlayerInputComponent->BindAction("RClick", IE_Pressed, GearManager, &UGearManagementComponent::OnRClickHit);
	PlayerInputComponent->BindAction("SpaceBar", IE_Pressed, GearManager, &UGearManagementComponent::OnSpaceHit);
	PlayerInputComponent->BindAction("Shift", IE_Pressed, GearManager, &UGearManagementComponent::OnShiftHit);
	PlayerInputComponent->BindAction("KeyQ", IE_Pressed, GearManager, &UGearManagementComponent::OnKeyQHit);
}

float ATacVehicle::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	DamageManager->HandleDamage(DamageAmount, DamageCauser);
	return DamageAmount;// TODO Changes return value
}

void ATacVehicle::MoveForward(float Val)
{
	GetVehicleMovementComponent()->SetThrottleInput(Val);
}

void ATacVehicle::MoveRight(float Val)
{
	GetVehicleMovementComponent()->SetSteeringInput(Val);
}

void ATacVehicle::PickupGear()
{
	PickupVolume->Pickup();
}

// Update player states which consists of OwnedGears and Transform
void ATacVehicle::UpdateState()
{
	ATacPlayerState* TacPS = Cast<ATacPlayerState>(PlayerState);
	GearManager->InitializeGear(TacPS->GetGears());
	SetActorTransform(TacPS->GetTacTransform(), false, nullptr, ETeleportType::TeleportPhysics);
}

void ATacVehicle::RotateCamera(float val)
{
	SpringArm->AddRelativeRotation(FRotator(0.f, val, 0.f));
}

void ATacVehicle::LiftCamera(float val)
{
	auto LiftAngle = SpringArm->RelativeRotation.Pitch;
	// Lift angle need to be limited from 0 deg to -90 deg
	if (LiftAngle < -80.f && val < 0.f) { return; }
	if (LiftAngle > 5.f && val > 0.f) { return; }
	SpringArm->AddRelativeRotation(FRotator(val, 0.f, 0.f));
}

void ATacVehicle::ZoomCamera(float val)
{
	SpringArm->TargetArmLength += val * -10.f;
}

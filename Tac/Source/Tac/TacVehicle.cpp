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
#include "Ejector.h"
#include "EjectorComponent.h"
#include "TacPlayerState.h"

ATacVehicle::ATacVehicle()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> TacMesh(TEXT("/Game/Tac/SK_Tac"));
	if (TacMesh.Object)
	{
		GetMesh()->SetSkeletalMesh(TacMesh.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> TacAnim(TEXT("/Game/Tac/AnimBP_TacPawn"));
	if (TacAnim.Class)
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(TacAnim.Class);
	}

	UWheeledVehicleMovementComponent4W* Vehicle4W = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovement());

	check(Vehicle4W->WheelSetups.Num() == 4);

	static ConstructorHelpers::FClassFinder<UVehicleWheel> FrontWheel(TEXT("/Game/Tac/BP_TacWheel_Front"));
	static ConstructorHelpers::FClassFinder<UVehicleWheel> RearWheel(TEXT("/Game/Tac/BP_TacWheel_Rear"));
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

	// Create the collect capsule component
	CollectCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollectCapsule"));
	CollectCapsule->SetupAttachment(RootComponent);
	CollectCapsule->SetCapsuleHalfHeight(750.f);
	CollectCapsule->SetCapsuleRadius(350.f);
	CollectCapsule->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));

	BoostSpeed = 400.f;


}

void ATacVehicle::BeginPlay()
{
	Super::BeginPlay();
	InitialGear();
}

void ATacVehicle::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATacVehicle::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATacVehicle::MoveRight);
	PlayerInputComponent->BindAxis("LookRight", this, &ATacVehicle::RotateCamera);
	PlayerInputComponent->BindAxis("LookUp", this, &ATacVehicle::LiftCamera);
	PlayerInputComponent->BindAxis("Zoom", this, &ATacVehicle::ZoomCamera);

	PlayerInputComponent->BindAction("Boost", IE_Pressed, this, &ATacVehicle::Boost);
	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &ATacVehicle::GetEjector);
	PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &ATacVehicle::OnHandbrakePressed);
	PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &ATacVehicle::OnHandbrakeReleased);
}

void ATacVehicle::MoveForward(float Val)
{
	GetVehicleMovementComponent()->SetThrottleInput(Val);

}

void ATacVehicle::MoveRight(float Val)
{
	GetVehicleMovementComponent()->SetSteeringInput(Val);
}

void ATacVehicle::OnHandbrakePressed()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
}

void ATacVehicle::OnHandbrakeReleased()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

void ATacVehicle::GetEjector()
{
	if (FindComponentByClass<UEjectorComponent>()) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Has EjectorComponent"));
		return; 
	}
	TArray<AActor*> EjectorInRange;
	CollectCapsule->GetOverlappingActors(EjectorInRange, AEjector::StaticClass());
	if (!EjectorInRange.IsValidIndex(0)) { return; }
	AEjector* EjectorActor = Cast<AEjector>(EjectorInRange[0]);
	EjectorActor->Destroy();
	EjectorInRange.Empty();
	FGear EjectorGear;
	EjectorGear.Gear = UEjectorComponent::StaticClass();
	EjectorGear.Socket = EGearSocket::EBack;
	SpawnGear(EjectorGear);
	AddToState(EjectorGear);
}

void ATacVehicle::SpawnGear(FGear GearToSet)
{
	auto Ejector = NewObject<UStaticMeshComponent>(this, GearToSet.Gear);
	Ejector->SetupAttachment(GetRootComponent(), FName(*GearToSet.GetSocketName()));
	Ejector->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Ejector->RegisterComponent();
}

void ATacVehicle::AddToState(FGear GearToAdd)
{
	ATacPlayerState* TacPS = Cast<ATacPlayerState>(PlayerState);
	TacPS->AddGear(GearToAdd);
}

void ATacVehicle::InitialGear()
{
	ATacPlayerState* TacPS = Cast<ATacPlayerState>(PlayerState);
	for (auto Gear : TacPS->GetGears())
	{
		SpawnGear(Gear);
	}
	SetActorTransform(TacPS->GetTacTransform(), false, nullptr, ETeleportType::TeleportPhysics);
	UE_LOG(LogTemp, Log, TEXT("%s"), *TacPS->GetTacTransform().ToString());
}

void ATacVehicle::RotateCamera(float val)
{
	SpringArm->AddRelativeRotation(FRotator(0.f, val, 0.f));
}

void ATacVehicle::LiftCamera(float val)
{
	auto LiftAngle = SpringArm->RelativeRotation.Pitch;
	UE_LOG(LogTemp, Log, TEXT("%f"), LiftAngle);
	if (LiftAngle < -80.f && val < 0.f) { return; }
	if (LiftAngle > 5.f && val > 0.f) { return; }
	SpringArm->AddRelativeRotation(FRotator(val, 0.f, 0.f));
}

void ATacVehicle::ZoomCamera(float val)
{
	SpringArm->TargetArmLength += val * -10.f;
}

void ATacVehicle::Boost()
{
	if (FindComponentByClass<UEjectorComponent>())
	{
		auto Boost = GetMesh()->GetForwardVector() * BoostSpeed;
		GetMesh()->AddImpulse(Boost, NAME_None, true);		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Don't have an ejector!"));
	}
}

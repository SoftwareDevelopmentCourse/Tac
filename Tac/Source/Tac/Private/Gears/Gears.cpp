// Copyright by GameDream.

#include "Tac.h"
#include "Gears.h"
#include "TacVehicle.h"
#include "TacHeader.h"

// Sets default values
AGears::AGears()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	/*==========================================
		Gear component initialize
	===========================================*/
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	/*==========================================
		Timeline triggered event initialize
	===========================================*/
	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curvy(TEXT("CurveFloat'/Game/Tac/Gears/Curve_GearsHover_Float.Curve_GearsHover_Float'"));
	if (Curvy.Object)
	{
		TimelineCurve = Curvy.Object;
	}
	Timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("FloatTimeline"));
	Timeline->SetTimelineLength(1.5f);
	Timeline->SetLooping(true);
	InterpFunction.BindUFunction(this, FName{ TEXT("GearsHover") });

	/*===========================================
		Properties initialize
	============================================*/
	FloatRange = 5.f;
	GearSocket = EGearSocket::ENull;
	GearName = TEXT("DEFAULT_NAME");
	GearType = EGearType::EProtector;
	SpawnRate = 3;
	MaxExistenceBase = -1;
	MaxExistenceOutdoors = 5;
	CostBase = 150;
	CostOutdoors = 100;
	bShouldRotate = false;

}

// Called when the game starts or when spawned
void AGears::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGears::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Add gear's rotation judged by whether gear is be picked up
	if (bShouldRotate)
	{
		AddGearRotation();
	}
}

// Gears hover 
void AGears::GearsHover(float val)
{
	auto CurrentLocation = Root->GetComponentLocation(); // TODO Add actor location
	auto NewLocationZ = CurrentLocation.Z + val * FloatRange;
	auto NewLoaction = FVector(CurrentLocation.X, CurrentLocation.Y, NewLocationZ);
	Root->SetRelativeLocation(NewLoaction);
}

// Called from GearSpawnVolume
void AGears::WorldSpawn()
{
	bShouldRotate = true;
	// Initialize timeline
	Timeline->AddInterpFloat(TimelineCurve, InterpFunction);
	Timeline->PlayFromStart();
}

// Add gears rotation
void AGears::AddGearRotation()
{
	Root->AddRelativeRotation(FRotator(0.f, 5.f, 0.f));
}

void AGears::OnLookUp(float val)
{
	// For overridden by child class
}

void AGears::OnLookRight(float val)
{
	// For overridden by child class
}

void AGears::OnSpaceHit(AActor* Target)
{
	// For overridden by child class
}

void AGears::OnShiftHit(AActor* Target)
{
	// For overridden by child class
}

void AGears::OnKeyQHit(AActor* Target)
{
	//UE_LOG(LogTemp, Error, TEXT("%s"), *OwnerVehicle->GetName());
	// For overridden by child class
}

void AGears::OnLClickHit(AActor* Target)
{
	// For overridden by child class
}

void AGears::OnRClickHit(AActor* Target)
{
	// For overridden by child class
}

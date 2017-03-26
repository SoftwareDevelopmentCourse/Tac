// Copyright by GameDream.

#include "Tac.h"
#include "Gears.h"
#include "TacHeader.h"
#include "GearComponent.h"

// Sets default values
AGears::AGears()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	/*==========================================
		Gear component initialize
	===========================================*/
	GearComp = CreateDefaultSubobject<UGearComponent>(TEXT("GearComponent"));
	RootComponent = GearComp;

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
	
	Gear.Socket = EGearSocket::EBack;
	Gear.GearName = TEXT("Debug");
	Gear.Type = EGearType::EBoost;
	Gear.GearComp = GearComp;
	SpawnRate = 3;
	MaxExistenceBase = -1;
	MaxExistenceOutdoors = 5;
	CostBase = 150;
	CostOutdoors = 100;
	bPickedup = false;

}

// Called when the game starts or when spawned
void AGears::BeginPlay()
{
	Super::BeginPlay();
	// Initialize timeline
	Timeline->AddInterpFloat(TimelineCurve, InterpFunction);
	Timeline->PlayFromStart();
}

// Called every frame
void AGears::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bPickedup)
	{
		AddGearRotation();
	}
}

// Gears hover 
void AGears::GearsHover(float val)
{
	auto CurrentLocation = GearComp->GetComponentLocation(); // TODO Add actor location
	auto NewLocationZ = CurrentLocation.Z + val * FloatRange;
	auto NewLoaction = FVector(CurrentLocation.X, CurrentLocation.Y, NewLocationZ);
	GearComp->SetRelativeLocation(NewLoaction);
}

void AGears::OnPickedup()
{
	bPickedup = true;
	Timeline->Stop();
	//Destroy();
	// TODO Destroy actor when being picked up
}

// Add gears rotation
void AGears::AddGearRotation()
{
	GearComp->AddRelativeRotation(FRotator(0.f, 5.f, 0.f));
}


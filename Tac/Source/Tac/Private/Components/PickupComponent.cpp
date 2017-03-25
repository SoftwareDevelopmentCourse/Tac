// Copyright by GameDream.

#include "Tac.h"
#include "PickupComponent.h"
#include "Gears.h"
#include "TacHeader.h"
#include "GearManagementComponent.h"
#include "TacVehicle.h"


// Sets default values for this component's properties
UPickupComponent::UPickupComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	PickupCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PickupCapsule"));
	PickupCapsule->SetupAttachment(this);
	PickupCapsule->SetCapsuleHalfHeight(750.f);
	PickupCapsule->SetCapsuleRadius(350.f);
	PickupCapsule->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));

}


// Called when the game starts
void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UPickupComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPickupComponent::Pickup()
{
	TArray<AActor*> ActorsInRange;
	PickupCapsule->GetOverlappingActors(ActorsInRange, AGears::StaticClass());
	if (!ActorsInRange.IsValidIndex(0)) { return; }
	AGears* Gear = Cast<AGears>(ActorsInRange[0]);
	Gear->Destroy();
	ActorsInRange.Empty();
	FGear GearToSet;
	GearToSet.Gear = AGears::StaticClass();
	GearToSet.Socket = EGearSocket::EBack;
	ATacVehicle* Owner = Cast<ATacVehicle>(GetOwner());
	UGearManagementComponent* Manager = Cast<UGearManagementComponent>(Owner->GetGearManager());
	Manager->SpawnGear(GearToSet);
	Manager->UpdateData(GearToSet);
}
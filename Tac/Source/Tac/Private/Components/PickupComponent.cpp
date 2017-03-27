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

	// Initialize owner vehicle, for some reason, the GetOwner() function can only be used once in Constructor
	OwnerVehicle = Cast<ATacVehicle>(GetOwner());

}

// Called when the game starts
void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize here, GetOwner() could be used here
	PickupCapsule = OwnerVehicle->PickupCapsule;
}


// Called every frame
void UPickupComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPickupComponent::Pickup()
{
	// Try to get gear in range
	TArray<AActor*> ActorsInRange;
	PickupCapsule->GetOverlappingActors(ActorsInRange, AGears::StaticClass());
	if (!ActorsInRange.IsValidIndex(0)) { return; }
	AGears* Gear = Cast<AGears>(ActorsInRange[0]);
	ActorsInRange.Empty();
	// Try to add the gear to tac
	UGearManagementComponent* Manager = Cast<UGearManagementComponent>(OwnerVehicle->GetGearManager());
	Manager->TryAddGear(Gear->GetClass()); // TODO Try add gear reference 
}
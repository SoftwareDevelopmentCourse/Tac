// Copyright by GameDream.

#include "Tac.h"
#include "Components/GearManagementComponent.h"
#include "TacHeader.h"
#include "TacVehicle.h"
#include "TacPlayerState.h"


// Sets default values for this component's properties
UGearManagementComponent::UGearManagementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	OwnerVehicle = Cast<ATacVehicle>(GetOwner());
	
}


// Called when the game starts
void UGearManagementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UGearManagementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGearManagementComponent::SpawnGear(FGear GearToSet)
{
	auto Gear = NewObject<UStaticMeshComponent>(OwnerVehicle, GearToSet.Gear);
	Gear->SetupAttachment(OwnerVehicle->GetRootComponent(), FName(*GearToSet.GetSocketName()));
	Gear->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Gear->RegisterComponent();
}

void UGearManagementComponent::UpdateData(FGear GearToAdd)
{
	ATacPlayerState* OwnerPS = Cast<ATacPlayerState>(OwnerVehicle->PlayerState);
	OwnerPS->AddGear(GearToAdd);
}

void UGearManagementComponent::OnSpaceHit()
{
}

void UGearManagementComponent::OnShiftHit()
{
}

void UGearManagementComponent::OnKeyQHit()
{
}

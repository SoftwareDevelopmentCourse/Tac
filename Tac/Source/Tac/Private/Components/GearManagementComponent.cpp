// Copyright by GameDream.

#include "Tac.h"
#include "Components/GearManagementComponent.h"
#include "TacHeader.h"
#include "TacVehicle.h"
#include "GearComponent.h"
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
	OwnerPS = Cast<ATacPlayerState>(OwnerVehicle->PlayerState);
	
	// ...
	OwnerVehicle->InputComponent->BindAxis("LookUp", this, &UGearManagementComponent::OnLookUp);
	OwnerVehicle->InputComponent->BindAxis("LookRight", this, &UGearManagementComponent::OnLookRight);
	OwnerVehicle->InputComponent->BindAction("SpaceBar", IE_Pressed, this, &UGearManagementComponent::OnSpaceHit);
	OwnerVehicle->InputComponent->BindAction("Shift", IE_Pressed, this, &UGearManagementComponent::OnShiftHit);
	//OwnerVehicle->InputComponent->BindAction("Shift", IE_Released, this, &UGearManagementComponent::);
	OwnerVehicle->InputComponent->BindAction("KeyQ", IE_Pressed, this, &UGearManagementComponent::OnKeyQHit);
	//OwnerVehicle->InputComponent->BindAction("KeyQ", IE_Released, this, &UGearManagementComponent::);
}

// Called every frame
void UGearManagementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGearManagementComponent::SpawnGear(FGear GearToSet)
{
	/*
		auto Gear = NewObject<UGearComponent>(OwnerVehicle, GearToSet.GearComp);
		Gear->SetupAttachment(OwnerVehicle->GetRootComponent(), FName(*GearToSet.GetSocketName()));
		Gear->GetGearMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Gear->RegisterComponent();
	*/

}

void UGearManagementComponent::UpdateData(FGear GearToAdd)
{
	OwnerPS->AddGear(GearToAdd);
}

void UGearManagementComponent::TryAddGear(FGear GearToAdd)
{
}

void UGearManagementComponent::OnLookUp(float val)
{
}

void UGearManagementComponent::OnLookRight(float val)
{
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

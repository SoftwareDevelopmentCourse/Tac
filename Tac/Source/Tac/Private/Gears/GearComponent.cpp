// Copyright by GameDream.

#include "Tac.h"
#include "GearComponent.h"


// Sets default values for this component's properties
UGearComponent::UGearComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	//GearMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GearMesh"));
	//GearMesh->SetupAttachment(this);
	//GearMesh->BodyInstance.SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}


// Called when the game starts
void UGearComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGearComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


// Copyright by GameDream.

#include "Tac.h"
#include "DamageComponent.h"


// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDamageComponent::RecoverArmor()
{
}

void UDamageComponent::StopRecoverArmor()
{
}

void UDamageComponent::RecoverHealth()
{
}

void UDamageComponent::HandleDamage()
{
}


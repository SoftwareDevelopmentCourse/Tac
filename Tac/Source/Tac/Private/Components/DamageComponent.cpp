// Copyright by GameDream.

#include "Tac.h"
#include "DamageComponent.h"
#include "Gear_Gun.h"


// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	MaxHealth = 100;
	MaxArmor = 100;
	Health = MaxHealth;
	Armor = MaxArmor;
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

void UDamageComponent::RecoverHealth(int32 val)
{
	Health = FMath::Clamp<int32>(Health + val, val, MaxHealth);
}

void UDamageComponent::HandleDamage(float DamageVal, AActor* DamageCauser)
{
	auto Penetration = Cast<AGear_Gun>(DamageCauser)->ArmorPenetration;
	float DamVal;
	if (Armor <= 0)
	{
		DamVal = DamageVal;
	}
	else
	{
		DamVal = DamageVal * Penetration;
		Armor = FMath::Clamp<int32>(Armor - DamVal * 0.5, 0, MaxArmor);
	}
	Health = FMath::Clamp<int32>(Health - DamVal, 0, MaxHealth);
	UE_LOG(LogTemp, Log, TEXT("\nHealth: %i	DamageReceived: %i\nArmor: %i"), Health, (int32)DamVal, Armor);
}


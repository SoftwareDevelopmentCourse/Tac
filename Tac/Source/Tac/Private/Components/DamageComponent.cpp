// Copyright by GameDream.

#include "Tac.h"
#include "DamageComponent.h"
#include "UnrealNetwork.h"
#include "Gear_Gun.h"


// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bReplicates = true;
	// ...
	MaxHealth = 100;
	MaxArmor = 100.f;
	Health = MaxHealth;
	Armor = MaxArmor;
	ArmorRecoveryDelay = 5.f;
	ArmorRecoveryRate = 2.5f;
}

void UDamageComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UDamageComponent, Health);
	DOREPLIFETIME(UDamageComponent, Armor);
	DOREPLIFETIME(UDamageComponent, MaxHealth);
	DOREPLIFETIME(UDamageComponent, MaxArmor);
}

// Called when the game starts
void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GetWorld()->GetTimerManager().SetTimer(ArmorRecoveryHandle, this, &UDamageComponent::RecoverArmor, ArmorRecoveryDelay);
	
}


// Called every frame
void UDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (bShouldRecoverArmor)
	{
		Armor = FMath::Clamp<float>(Armor + DeltaTime * 10 * ArmorRecoveryRate, Armor, MaxArmor);
		//UE_LOG(LogTemp, Log, TEXT("%f"), Armor);
		if (Armor == MaxArmor)
		{
			bShouldRecoverArmor = false;
		}
	}
}

void UDamageComponent::RecoverArmor()
{
	bShouldRecoverArmor = true;
	//UE_LOG(LogTemp, Warning, TEXT("Recovery"));
}

void UDamageComponent::StopRecoverArmor()
{
	bShouldRecoverArmor = false;
	//UE_LOG(LogTemp, Warning, TEXT("StopRecovery"));
	GetWorld()->GetTimerManager().ClearTimer(ArmorRecoveryHandle);
	GetWorld()->GetTimerManager().SetTimer(ArmorRecoveryHandle, this, &UDamageComponent::RecoverArmor, ArmorRecoveryDelay);
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
		Armor = FMath::Clamp<float>(Armor - DamVal * 0.5, 0, MaxArmor);
	}
	Health = FMath::Clamp<int32>(Health - DamVal, 0, MaxHealth);
	StopRecoverArmor();
	//UE_LOG(LogTemp, Log, TEXT("\nHealth: %i	DamageReceived: %i\nArmor: %i"), Health, (int32)DamVal, (int32)Armor);
}


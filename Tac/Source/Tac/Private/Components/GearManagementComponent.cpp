// Copyright by GameDream.

#include "Tac.h"
#include "Components/GearManagementComponent.h"
#include "TacHeader.h"
#include "TacVehicle.h"
#include "TacPlayerState.h"
#include "Gears.h"


// Sets default values for this component's properties
UGearManagementComponent::UGearManagementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize owner vehicle, for some reason, the GetOwner() function can only be used once in Constructor
	OwnerVehicle = Cast<ATacVehicle>(GetOwner());
	// Initialize judging conditions
	bShiftBind = false;
	bSpaceBind = false;
	bKeyQBind = false;
	bLClickBind = false;
	bRClickBind = false;
	bMouseBind = false;
	bHasFront = false;
	bHasBack = false;
	bHasLeft = false;
	bHasRight = false;
	bShouldDestroy = false;
}

// Called when the game starts
void UGearManagementComponent::BeginPlay()
{
	Super::BeginPlay();
	/*======================================
		Initialize here, GetOwner() could
		be used in BeginPlay()
	======================================*/
	OwnerPS = Cast<ATacPlayerState>(OwnerVehicle->PlayerState);

	/*====================================
		Bind input	
	====================================*/
	OwnerVehicle->InputComponent->BindAxis("LookUp", this, &UGearManagementComponent::OnLookUp);
	OwnerVehicle->InputComponent->BindAxis("LookRight", this, &UGearManagementComponent::OnLookRight);
	OwnerVehicle->InputComponent->BindAction("LClick", IE_Pressed, this, &UGearManagementComponent::OnLClickHit);
	OwnerVehicle->InputComponent->BindAction("RClick", IE_Pressed, this, &UGearManagementComponent::OnRClickHit);
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

void UGearManagementComponent::SpawnGear(TSubclassOf<AGears> GearToSpawn)
{
	AGears* GearObj = Cast<AGears>(GearToSpawn->GetDefaultObject()); // TODO Tac spawns child gear
	JudgeByType(GearToSpawn);
	OwnedGears.Add(GearObj);
}

void UGearManagementComponent::UpdateData(TSubclassOf<AGears> GearToAdd)
{
	OwnerPS->AddGear(GearToAdd);
	AGears* GearObj = Cast<AGears>(GearToAdd->GetDefaultObject());
	OwnedGears.Add(GearObj);
}

void UGearManagementComponent::TryPickup(AGears * GearToPickup)
{
	TSubclassOf<AGears> GearClass = GearToPickup->GetClass();

}

/*========================================================
	Calls different functions depends on gear's type
========================================================*/
void UGearManagementComponent::OnLookUp(float val)
{
	if (!bMouseBind) { return; }
	for (auto Gear : OwnedGears)
	{
		if (Gear->GearType == EGearType::EShoot)
		{
			Gear->OnLookUp(val);
		}
	}
}

void UGearManagementComponent::OnLookRight(float val)
{
	if (!bMouseBind) { return; }
	for (auto Gear : OwnedGears)
	{
		if (Gear->GearType == EGearType::EShoot)
		{
			Gear->OnLookRight(val);
		}
	}

}

void UGearManagementComponent::OnSpaceHit()
{
	if (!bSpaceBind) { return; }
	for (auto Gear : OwnedGears)
	{
		if (Gear->GearType == EGearType::EJump)
		{
			Gear->OnSpaceHit();
		}
	}
}

void UGearManagementComponent::OnShiftHit()
{
	if (!bShiftBind) { return; }
	for (auto Gear : OwnedGears)
	{
		if (Gear->GearType == EGearType::EBoost)
		{
			Gear->OnShiftHit();
		}
	}
}

void UGearManagementComponent::OnKeyQHit()
{
	if (!bKeyQBind) { return; }
	for (auto Gear : OwnedGears)
	{
		if (Gear->GearType == EGearType::EThrow)
		{
			Gear->OnKeyQHit();
		}
	}
}

void UGearManagementComponent::OnLClickHit()
{
	if (!bLClickBind) { return; }
	for (auto Gear : OwnedGears)
	{
		if (Gear->GearType == EGearType::EShoot)
		{
			Gear->OnLClickHit();
		}
	}
}

void UGearManagementComponent::OnRClickHit()
{
	if (!bRClickBind) { return; }
	for (auto Gear : OwnedGears)
	{
		if (Gear->GearType == EGearType::EShoot)
		{
			Gear->OnRClickHit();
		}
	}
}

/*================================================================
	Judges by gear's socket and type, and spawns gear to tac
================================================================*/
void UGearManagementComponent::JudgeBySocket(TSubclassOf<AGears> GearToJudge)
{
	switch (GearToJudge->GetDefaultObject<AGears>()->GearSocket)
	{
	case EGearSocket::ENull:
		break;
	case EGearSocket::ELeft:
		if (bHasLeft) { break; }
		bHasLeft = true;
		OwnerVehicle->GearActorLeft->SetChildActorClass(GearToJudge);
		OwnerVehicle->GearActorLeft->CreateChildActor();
		break;
	case EGearSocket::ERight:
		if (bHasRight) { break; }
		bHasRight = true;
		OwnerVehicle->GearActorRight->SetChildActorClass(GearToJudge);
		OwnerVehicle->GearActorRight->CreateChildActor();
		break;
	case EGearSocket::EFront:
		if (bHasFront) { break; }
		bHasFront = true;
		OwnerVehicle->GearActorFront->SetChildActorClass(GearToJudge);
		OwnerVehicle->GearActorFront->CreateChildActor();
		break;
	case EGearSocket::EBack:
		if (bHasBack) { break; }
		bHasBack = true;
		OwnerVehicle->GearActorBack->SetChildActorClass(GearToJudge);
		OwnerVehicle->GearActorBack->CreateChildActor();
		break;
	default:
		break;
	}
}

void UGearManagementComponent::JudgeByType(TSubclassOf<AGears> GearToJudge)
{
	switch (GearToJudge->GetDefaultObject<AGears>()->GearType)
	{
	case EGearType::EBoost:
		if (bShiftBind) { break; }
		bShiftBind = true;
		JudgeBySocket(GearToJudge);
		break;
	case EGearType::EJump:
		if (bSpaceBind) { break; }
		bSpaceBind = true;
		JudgeBySocket(GearToJudge);
		break;
	case EGearType::EProtector:
		JudgeBySocket(GearToJudge);
		break;
	case EGearType::EShoot:
		if (bLClickBind) { break; }
		bLClickBind = true;
		JudgeBySocket(GearToJudge);
		break;
	case EGearType::EThrow:
		if (bKeyQBind) { break; }
		bKeyQBind = true;
		JudgeBySocket(GearToJudge);
		break;
	default:
		break;
	}
}

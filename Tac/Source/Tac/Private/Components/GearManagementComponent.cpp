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
	// Initialize 4 sockets
	TacGears.SetNum(4);
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
}

// Called when the game starts
void UGearManagementComponent::BeginPlay()
{
	Super::BeginPlay();
	/*======================================
		Initialize here, GetOwner() could
		be used in BeginPlay()
	======================================*/
	if (OwnerVehicle)
	{
		OwnerPS = Cast<ATacPlayerState>(OwnerVehicle->PlayerState);
		/*====================================
		Bind input
		====================================*/
		//OwnerVehicle->InputComponent->BindAxis("LookUp", this, &UGearManagementComponent::OnLookUp);
		//OwnerVehicle->InputComponent->BindAxis("LookRight", this, &UGearManagementComponent::OnLookRight);
		//OwnerVehicle->InputComponent->BindAction("LClick", IE_Pressed, this, &UGearManagementComponent::OnLClickHit);
		//OwnerVehicle->InputComponent->BindAction("RClick", IE_Pressed, this, &UGearManagementComponent::OnRClickHit);
		//OwnerVehicle->InputComponent->BindAction("SpaceBar", IE_Pressed, this, &UGearManagementComponent::OnSpaceHit);
		//OwnerVehicle->InputComponent->BindAction("Shift", IE_Pressed, this, &UGearManagementComponent::OnShiftHit);
		////OwnerVehicle->InputComponent->BindAction("Shift", IE_Released, this, &UGearManagementComponent::);
		//OwnerVehicle->InputComponent->BindAction("KeyQ", IE_Pressed, this, &UGearManagementComponent::OnKeyQHit);
		////OwnerVehicle->InputComponent->BindAction("KeyQ", IE_Released, this, &UGearManagementComponent::);
	}
}

// Called every frame
void UGearManagementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGearManagementComponent::InitializeGear(TArray<TSubclassOf<AGears>> OwnedGears)
{
	ResetGears();
	for (int32 GearIndex = 0; GearIndex < 4; GearIndex++)
	{
		JudgeByType(OwnedGears[GearIndex].GetDefaultObject());
	}
}

void UGearManagementComponent::UpdateData(AGears* GearToAdd)
{
	OwnerPS->AddGear(GearToAdd->GetClass());
}

void UGearManagementComponent::TryPickup(AGears * GearToPickup)
{
	if (JudgeByType(GearToPickup))
	{
		GearToPickup->Destroy();
		UpdateData(GearToPickup);
	}
}

void UGearManagementComponent::ResetGears()
{

	auto Left = OwnerVehicle->GearActorLeft;
	auto Right = OwnerVehicle->GearActorRight;
	auto Front = OwnerVehicle->GearActorFront;
	auto Back = OwnerVehicle->GearActorBack;

	TacGears.Empty();
	Left->SetChildActorClass(AGears::StaticClass());
	Left->CreateChildActor();
	TacGears.Push(Left->GetChildActor());
	
	Right->SetChildActorClass(AGears::StaticClass());
	Right->CreateChildActor();
	TacGears.Push(Right->GetChildActor());
	
	Front->SetChildActorClass(AGears::StaticClass());
	Front->CreateChildActor();
	TacGears.Push(Front->GetChildActor());
	
	Back->SetChildActorClass(AGears::StaticClass());
	Back->CreateChildActor();
	TacGears.Push(Back->GetChildActor());
	
	InitializeState();
}

/*========================================================
	Calls different functions depends on gear's type
======================================================*/
void UGearManagementComponent::OnLookUp(float val)
{
	if (!bMouseBind) { return; }
	for (auto Actor : TacGears)
	{
		auto Gear = Cast<AGears>(Actor);
		if (Gear->GearType == EGearType::EShoot)
		{
			Gear->OnLookUp(val);
		}
	}
}

void UGearManagementComponent::OnLookRight(float val)
{
	if (!bMouseBind) { return; }
	for (auto Actor : TacGears)
	{
		auto Gear = Cast<AGears>(Actor);
		if (Gear->GearType == EGearType::EShoot)
		{
			Gear->OnLookRight(val);
		}
	}
}

void UGearManagementComponent::OnSpaceHit()
{
	if (!bSpaceBind) { return; }
	for (auto Actor : TacGears)
	{
		auto Gear = Cast<AGears>(Actor);
		if (Gear->GearType == EGearType::EJump)
		{
			Gear->OnSpaceHit(OwnerVehicle);
		}
	}
}

void UGearManagementComponent::OnShiftHit()
{
	if (!bShiftBind) { return; }
	for (auto Actor : TacGears)
	{
		auto Gear = Cast<AGears>(Actor);
		if (Gear->GearType == EGearType::EBoost)
		{
			Gear->OnShiftHit(OwnerVehicle);
		}
	}
}

void UGearManagementComponent::OnKeyQHit()
{
	if (!bKeyQBind) { return; }
	for (auto Actor : TacGears)
	{
		auto Gear = Cast<AGears>(Actor);
		if (Gear->GearType == EGearType::EThrow)
		{
			Gear->OnKeyQHit(OwnerVehicle);
		}
	}
}

void UGearManagementComponent::OnLClickHit()
{
	if (!bLClickBind) { return; }
	for (auto Actor : TacGears)
	{
		auto Gear = Cast<AGears>(Actor);
		if (Gear->GearType == EGearType::EShoot)
		{
			Gear->OnLClickHit(OwnerVehicle);
		}
	}
}

void UGearManagementComponent::OnRClickHit()
{
	if (!bRClickBind) { return; }
	for (auto Actor : TacGears)
	{
		auto Gear = Cast<AGears>(Actor);
		if (Gear->GearType == EGearType::EShoot)
		{
			Gear->OnRClickHit(OwnerVehicle);
		}
	}
}

/*================================================================
	Judges by gear's socket and type, and spawns gear to tac
================================================================*/
bool UGearManagementComponent::JudgeBySocket(AGears* GearToJudge)
{
	auto Left = OwnerVehicle->GearActorLeft;
	auto Right = OwnerVehicle->GearActorRight;
	auto Front = OwnerVehicle->GearActorFront;
	auto Back = OwnerVehicle->GearActorBack;

	switch (GearToJudge->GearSocket)
	{
	case EGearSocket::ENull:
		return false;
	case EGearSocket::ELeft:
		if (bHasLeft) { return false; }
		bHasLeft = true;
		Left->SetChildActorClass(GearToJudge->GetClass());
		Left->CreateChildActor();
		TacGears[0] = Left->GetChildActor();
		return true;
	case EGearSocket::ERight:
		if (bHasRight) { return false; }
		bHasRight = true;
		Right->SetChildActorClass(GearToJudge->GetClass());
		Right->CreateChildActor();
		TacGears[1] = Right->GetChildActor();
		return true;
	case EGearSocket::EFront:
		if (bHasFront) { return false; }
		bHasFront = true;
		Front->SetChildActorClass(GearToJudge->GetClass());
		Front->CreateChildActor();
		TacGears[2] = Front->GetChildActor();
		return true;
	case EGearSocket::EBack:
		if (bHasBack) { return false; }
		bHasBack = true;
		Back->SetChildActorClass(GearToJudge->GetClass());
		Back->CreateChildActor();
		TacGears[3] = Back->GetChildActor();
		return true;
	default:
		return false;
	}
}

bool UGearManagementComponent::JudgeByType(AGears* GearToJudge)
{
	switch (GearToJudge->GearType)
	{
	case EGearType::EBoost:
		if (bShiftBind) { return false; }
		bShiftBind = true;
		return JudgeBySocket(GearToJudge);
	case EGearType::EJump:
		if (bSpaceBind) { return false; }
		bSpaceBind = true;
		return JudgeBySocket(GearToJudge);
	case EGearType::EProtector:
		return JudgeBySocket(GearToJudge);
	case EGearType::EShoot:
		if (bLClickBind) { return false; }
		bLClickBind = true;
		return JudgeBySocket(GearToJudge);
	case EGearType::EThrow:
		if (bKeyQBind) { return false; }
		bKeyQBind = true;
		return JudgeBySocket(GearToJudge);
	default:
		return false;
	}
}

void UGearManagementComponent::InitializeState()
{
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
}

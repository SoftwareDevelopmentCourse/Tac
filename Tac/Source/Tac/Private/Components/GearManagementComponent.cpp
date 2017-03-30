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

void UGearManagementComponent::InitializeGear(AGears* GearToSpawn)
{

	InitializeState();
	
	if (!JudgeByType(GearToSpawn))
	{

	}
	
	//OwnedGears = OwnerPS->GetGears();
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
	//Left->CreateChildActor();
	
	Right->SetChildActorClass(AGears::StaticClass());
	//Right->CreateChildActor();
	
	Front->SetChildActorClass(AGears::StaticClass());
	//Front->CreateChildActor();
	
	Back->SetChildActorClass(AGears::StaticClass());
	//Back->CreateChildActor();
	
	InitializeState();
}

/*========================================================
	Calls different functions depends on gear's type
======================================================*/
void UGearManagementComponent::OnLookUp(float val)
{
	if (!bMouseBind) { return; }
	/*
	for (auto Gear : OwnerPS->GetGears())
	{
		if (Gear.GetDefaultObject()->GearType == EGearType::EShoot)
		{
			Gear.GetDefaultObject()->OnLookUp(val);
		}
	}
	*/

}

void UGearManagementComponent::OnLookRight(float val)
{
	if (!bMouseBind) { return; }
	/*
	for (auto Gear : OwnerPS->GetGears())
	{
		if (Gear.GetDefaultObject()->GearType == EGearType::EShoot)
		{
			Gear.GetDefaultObject()->OnLookRight(val);
		}
	}
	*/
}

void UGearManagementComponent::OnSpaceHit()
{
	if (!bSpaceBind) { return; }
	/*
	for (auto Actor : TacGears)
	{
		auto Gear = Cast<AGears>(Actor);
		if (Gear->GearType == EGearType::EJump)
		{
			Gear->OnSpaceHit();
		}
	}
	*/
}

void UGearManagementComponent::OnShiftHit()
{
	if (!bShiftBind) { return; }
	for (auto Gear : TacGears)
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
	/*
	for (auto Gear : OwnedGears)
	{
		if (Gear->GearType == EGearType::EThrow)
		{
			Gear->OnKeyQHit();
		}
	}
	*/
}

void UGearManagementComponent::OnLClickHit()
{
	if (!bLClickBind) { return; }
	/*
		for (auto Gear : OwnedGears)
	{
		if (Gear->GearType == EGearType::EShoot)
		{
			Gear->OnLClickHit();
		}
	}
	*/

}

void UGearManagementComponent::OnRClickHit()
{
	if (!bRClickBind) { return; }
	/*
		for (auto Gear : OwnedGears)
	{
		if (Gear->GearType == EGearType::EShoot)
		{
			Gear->OnRClickHit();
		}
	}
	*/
}

/*================================================================
	Judges by gear's socket and type, and spawns gear to tac
================================================================*/
bool UGearManagementComponent::JudgeBySocket(AGears* GearToJudge)
{
	switch (GearToJudge->GearSocket)
	{
	case EGearSocket::ENull:
		//UE_LOG(LogTemp, Log, TEXT("Null class is : %s"), *GearToJudge->GetClass()->GetName());
		return false;
	case EGearSocket::ELeft:
		if (bHasLeft) { return false; }
		bHasLeft = true;
		OwnerVehicle->GearActorLeft->SetChildActorClass(GearToJudge->GetClass());
		//UE_LOG(LogTemp, Log, TEXT("Left class is : %s"), *GearToJudge->GetClass()->GetName());
		OwnerVehicle->GearActorLeft->CreateChildActor();
		TacGears.Push(Cast<AGears>(OwnerVehicle->GearActorLeft->GetChildActor()));
		return true;
	case EGearSocket::ERight:
		if (bHasRight) { return false; }
		bHasRight = true;
		OwnerVehicle->GearActorRight->SetChildActorClass(GearToJudge->GetClass());
		//UE_LOG(LogTemp, Log, TEXT("Right class is : %s"), *GearToJudge->GetClass()->GetName());
		OwnerVehicle->GearActorRight->CreateChildActor();
		TacGears.Push(Cast<AGears>(OwnerVehicle->GearActorRight->GetChildActor()));
		return true;
	case EGearSocket::EFront:
		if (bHasFront) { return false; }
		bHasFront = true;
		OwnerVehicle->GearActorFront->SetChildActorClass(GearToJudge->GetClass());
		//UE_LOG(LogTemp, Log, TEXT("Front class is : %s"), *GearToJudge->GetClass()->GetName());
		OwnerVehicle->GearActorFront->CreateChildActor();
		TacGears.Push(Cast<AGears>(OwnerVehicle->GearActorFront->GetChildActor()));
		return true;
	case EGearSocket::EBack:
		if (bHasBack) { return false; }
		bHasBack = true;
		OwnerVehicle->GearActorBack->SetChildActorClass(GearToJudge->GetClass());
		//UE_LOG(LogTemp, Log, TEXT("Back class is : %s"), *GearToJudge->GetClass()->GetName());
		OwnerVehicle->GearActorBack->CreateChildActor();
		TacGears.Push(Cast<AGears>(OwnerVehicle->GearActorBack->GetChildActor()));
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

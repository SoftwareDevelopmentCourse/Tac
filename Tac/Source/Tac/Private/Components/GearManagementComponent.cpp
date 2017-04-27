// Copyright by GameDream.

#include "Tac.h"
#include "GearManagementComponent.h"
#include "TacHeader.h"
#include "TacVehicle.h"
#include "TacPlayerState.h"
#include "Gears.h"
#include "TacController.h"

// Sets default values for this component's properties
UGearManagementComponent::UGearManagementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bReplicates = true;
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
		int32 JudgeResult = 0;
		JudgeByType(OwnedGears[GearIndex].GetDefaultObject(), JudgeResult);
	}
}

bool UGearManagementComponent::TryPickup_Validate(AGears * GearToPickup)
{
	return true;
}

void UGearManagementComponent::TryPickup_Implementation(AGears * GearToPickup)
{
	int32 JudgeResult = 0;
	JudgeByType(GearToPickup, JudgeResult);
	if (JudgeResult >= 0 && JudgeResult <=3)
	{
		GearToPickup->Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, *GearToPickup->GetName());
		//OwnerPS->AddGear(GearIndex, GearToPickup->GetClass());
		//ATacController* TacCtrl = Cast<ATacController>(OwnerVehicle->Controller);
		//TacCtrl->AddGearSlot();
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

void UGearManagementComponent::JudgeByType(AGears* GearToJudge, int32 Result)
{
	switch (GearToJudge->GearType)
	{
	case EGearType::EBoost:
		if (bShiftBind) { Result = -1; }
		bShiftBind = true;
		Result = JudgeBySocket(GearToJudge);
	case EGearType::EJump:
		if (bSpaceBind) { Result = -1; }
		bSpaceBind = true;
		Result = JudgeBySocket(GearToJudge);
	case EGearType::EProtector:
		Result = JudgeBySocket(GearToJudge);
	case EGearType::EShoot:
		if (bLClickBind) { Result = -1; }
		bLClickBind = true;
		Result = JudgeBySocket(GearToJudge);
	case EGearType::EThrow:
		if (bKeyQBind) { Result = -1; }
		bKeyQBind = true;
		Result = JudgeBySocket(GearToJudge);
	default:
		Result = -1;
	}
}

int32 UGearManagementComponent::JudgeBySocket(AGears* GearToJudge)
{
	auto Left = OwnerVehicle->GearActorLeft;
	auto Right = OwnerVehicle->GearActorRight;
	auto Front = OwnerVehicle->GearActorFront;
	auto Back = OwnerVehicle->GearActorBack;
	AGears* Gear;
	switch (GearToJudge->GearSocket)
	{
	case EGearSocket::ENull:
		return -1;
	case EGearSocket::ELeft:
		if (bHasLeft) { return -1; }
		bHasLeft = true;
		Left->SetChildActorClass(GearToJudge->GetClass());
		Left->CreateChildActor();
		TacGears[0] = Left->GetChildActor();
		Gear = Cast<AGears>(TacGears[0]);
		Gear->bIsPicked = true;
		return 2;
	case EGearSocket::ERight:
		if (bHasRight) { return -1; }
		bHasRight = true;
		Right->SetChildActorClass(GearToJudge->GetClass());
		Right->CreateChildActor();
		TacGears[1] = Right->GetChildActor();
		Gear = Cast<AGears>(TacGears[1]);
		Gear->bIsPicked = true;
		return 3;
	case EGearSocket::EFront:
		if (bHasFront) { return -1; }
		bHasFront = true;
		Front->SetChildActorClass(GearToJudge->GetClass());
		Front->CreateChildActor();
		//Front->GetChildActor()->SetActorLocation(OwnerVehicle->GetRootComponent()->GetSocketLocation(TEXT("EFront")));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Front->GetName());
		TacGears[2] = Front->GetChildActor();
		Gear = Cast<AGears>(TacGears[2]);
		Gear->ResetLocation();
		Gear->bIsPicked = true;
		return 0;
	case EGearSocket::EBack:
		if (bHasBack) { return -1; }
		bHasBack = true;
		Back->SetChildActorClass(GearToJudge->GetClass());
		Back->CreateChildActor();
		TacGears[3] = Back->GetChildActor();
		Gear = Cast<AGears>(TacGears[3]);
		Gear->bIsPicked = true;
		return 1;
	default:
		return -1;
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

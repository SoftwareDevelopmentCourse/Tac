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

void UGearManagementComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&OutLifetimeProps)const
{
	DOREPLIFETIME(UGearManagementComponent, TacGears);
}

void UGearManagementComponent::InitializeGear(TArray<TSubclassOf<AGears>> OwnedGears)
{
	ResetGears();
	int32 JudgeResult = 0;
	for (int32 GearIndex = 0; GearIndex < 4; GearIndex++)
	{
		JudgeBySocket(OwnedGears[GearIndex].GetDefaultObject(), JudgeResult);
	}
}

bool UGearManagementComponent::TryPickup_Validate(AGears * GearToPickup)
{
	return true;
}

void UGearManagementComponent::TryPickup_Implementation(AGears * GearToPickup)
{
	int32 JudgeResult = 0;
	JudgeBySocket(GearToPickup, JudgeResult);
	if (JudgeResult >= 0 && JudgeResult <=3)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, *GearToPickup->GetName());
		//OwnerPS->AddGear(GearIndex, GearToPickup->GetClass());
		//ATacController* TacCtrl = Cast<ATacController>(OwnerVehicle->Controller);
		//TacCtrl->AddGearSlot();
	}
}

void UGearManagementComponent::ResetGears()
{
	TacGears.Empty();
	TacGears.SetNum(4);
	TArray<AActor*> AttachedActors;
	OwnerVehicle->GetAttachedActors(AttachedActors);
	for (auto Actor : AttachedActors)
	{
		AGears* Gear = Cast<AGears>(Actor);
		Gear->Destroy();
	}
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
		AGears* Gear = Cast<AGears>(Actor);
		if (Gear->GearBindKey != EGearBindKey::EMouseLook) { return; }
		Gear->OnLookUp(val);
	}
}

void UGearManagementComponent::OnLookRight(float val)
{
	if (!bMouseBind) { return; }
	for (auto Actor : TacGears)
	{
		AGears* Gear = Cast<AGears>(Actor);
		Gear->OnLookRight(val);
	}
}

void UGearManagementComponent::OnSpaceHit()
{
	if (!bSpaceBind) { return; }
	for (auto Actor : TacGears)
	{
		AGears* Gear = Cast<AGears>(Actor);
		Gear->OnSpaceHit(OwnerVehicle);
	}
}

void UGearManagementComponent::OnShiftHit()
{
	//if (!bShiftBind) { return; }
	for (auto Actor : TacGears)
	{
		AGears* Gear = Cast<AGears>(Actor);
		if (!Gear || Gear->GearBindKey != EGearBindKey::EShift)
		{ 
			continue; 
		}
		Gear->OnShiftHit(OwnerVehicle);
	}
}

void UGearManagementComponent::OnKeyQHit()
{
	if (!bKeyQBind) { return; }
	for (auto Actor : TacGears)
	{
		AGears* Gear = Cast<AGears>(Actor);
		Gear->OnKeyQHit(OwnerVehicle);
	}
}

bool UGearManagementComponent::OnLClickHit_Validate()
{
	return true;
}

void UGearManagementComponent::OnLClickHit_Implementation()
{
	//if (!bLClickBind) { return; }
	for (auto Actor : TacGears)
	{
		AGears* Gear = Cast<AGears>(Actor);
		if (!Gear || Gear->GearBindKey != EGearBindKey::ELClick)
		{
			continue;
		}
		Gear->OnLClickHit(OwnerVehicle);
	}
}

void UGearManagementComponent::OnRClickHit()
{
	if (!bRClickBind) { return; }
	for (auto Actor : TacGears)
	{
		AGears* Gear = Cast<AGears>(Actor);
		Gear->OnRClickHit(OwnerVehicle);
	}
}

void UGearManagementComponent::JudgeBySocket(AGears* GearToJudge, int32 Result)
{
	switch (GearToJudge->GearSocket)
	{
	case EGearSocket::ENull:
		Result = -1;
		break;
	case EGearSocket::EFront:
		if (bHasFront) { Result = -1; }
		bHasFront = true;
		GearToJudge->OnPicked();
		GearToJudge->AttachToActor(OwnerVehicle, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("EFront"));
		//UE_LOG(LogTemp, Warning, TEXT("\nOwner: %s\nNetOwner: %s\nNetOwningOwner: %s"), *GearToJudge->GetOwner()->GetName(), *GearToJudge->GetNetOwner()->GetName(), *GearToJudge->GetNetOwningPlayer()->GetName());
		TacGears[0] = GearToJudge;
		Result = 0;
		break;
	case EGearSocket::EBack:
		if (bHasBack) { Result = -1; }
		bHasBack = true;
		GearToJudge->OnPicked();
		GearToJudge->AttachToActor(OwnerVehicle, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("EBack"));
		TacGears[1] = GearToJudge;
		Result = 1;
		break;
	case EGearSocket::ELeft:
		if (bHasLeft) { Result = -1; }
		bHasLeft = true;
		GearToJudge->OnPicked();
		GearToJudge->AttachToActor(OwnerVehicle, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("ELeft"));
		TacGears[2] = GearToJudge;
		Result = 2;
		break;
	case EGearSocket::ERight:
		if (bHasRight) { Result = -1; }
		bHasRight = true;
		GearToJudge->OnPicked();
		GearToJudge->AttachToActor(OwnerVehicle, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("ERight"));
		TacGears[3] = GearToJudge;
		Result = 3;
		break;
	default:
		Result = -1;
		break;
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

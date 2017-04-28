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
		JudgeBySocket(OwnedGears[GearIndex].GetDefaultObject());
	}
}

bool UGearManagementComponent::TryPickup_Validate(AGears * GearToPickup)
{
	return true;
}

void UGearManagementComponent::TryPickup_Implementation(AGears * GearToPickup)
{
	auto JudgeResult = JudgeBySocket(GearToPickup);
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
	if (!bShiftBind) { return; }
	for (auto Actor : TacGears)
	{
		AGears* Gear = Cast<AGears>(Actor);
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

void UGearManagementComponent::OnLClickHit()
{
	if (!bLClickBind) { return; }
	for (auto Actor : TacGears)
	{
		AGears* Gear = Cast<AGears>(Actor);
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

int32 UGearManagementComponent::JudgeBySocket(AGears* GearToJudge)
{
	switch (GearToJudge->GearSocket)
	{
	case EGearSocket::ENull:
		return -1;
	case EGearSocket::EFront:
		if (bHasFront) { return -1; }
		bHasFront = true;
		//Front->GetChildActor()->SetActorLocation(OwnerVehicle->GetRootComponent()->GetSocketLocation(TEXT("EFront")));
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *Front->GetName());
		GearToJudge->OnPicked();
		GearToJudge->AttachToActor(OwnerVehicle, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("EFront"));
		TacGears[0] = GearToJudge;
		return 0;
	case EGearSocket::EBack:
		if (bHasBack) { return -1; }
		bHasBack = true;
		GearToJudge->OnPicked();
		GearToJudge->AttachToActor(OwnerVehicle, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("EBack"));
		TacGears[1] = GearToJudge;
		return 1;
	case EGearSocket::ELeft:
		if (bHasLeft) { return -1; }
		bHasLeft = true;
		GearToJudge->OnPicked();
		GearToJudge->AttachToActor(OwnerVehicle, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("ELeft"));
		TacGears[2] = GearToJudge;
		return 2;
	case EGearSocket::ERight:
		if (bHasRight) { return -1; }
		bHasRight = true;
		GearToJudge->OnPicked();
		GearToJudge->AttachToActor(OwnerVehicle, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("ERight"));
		TacGears[3] = GearToJudge;
		return 3;
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

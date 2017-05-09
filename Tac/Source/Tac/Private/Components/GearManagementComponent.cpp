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

	//TacGears.SetNum(4);
}

// Called when the game starts
void UGearManagementComponent::BeginPlay()
{
	Super::BeginPlay();

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
		ATacPlayerState* OwnerPS = Cast<ATacPlayerState>(OwnerVehicle->PlayerState);
		if (!OwnerPS) { return; }
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, *GearToPickup->GetName());
		OwnerPS->AddGear(JudgeResult, GearToPickup->GetClass());
		ATacController* TacCtrl = Cast<ATacController>(OwnerVehicle->Controller);
		TacCtrl->AddGearSlot(JudgeResult);
	}
}

void UGearManagementComponent::ResetGears()
{
	TacGears.Empty(4);
	TacGears.SetNum(4);
	TArray<AActor*> AttachedActors;
	OwnerVehicle->GetAttachedActors(AttachedActors);
	for (auto Actor : AttachedActors)
	{
		AGears* Gear = Cast<AGears>(Actor);
		Gear->Destroy();
	}
}

/*========================================================
	Calls different functions depends on gear's type
========================================================*/
bool UGearManagementComponent::OnLookUp_Validate(float val) { return true; }

void UGearManagementComponent::OnLookUp_Implementation(float val)
{
	if (!bMouseBind) { return; }
	for (auto Actor : TacGears)
	{
		AGears* Gear = Cast<AGears>(Actor);
		if (Gear->GearBindKey != EGearBindKey::EMouseLook) { return; }
		Gear->OnLookUp(val);
	}
}

bool UGearManagementComponent::OnLookRight_Validate(float val) { return true; }

void UGearManagementComponent::OnLookRight_Implementation(float val)
{
	if (!bMouseBind) { return; }
	for (auto Actor : TacGears)
	{
		AGears* Gear = Cast<AGears>(Actor);
		Gear->OnLookRight(val);
	}
}

bool UGearManagementComponent::OnSpaceHit_Validate() { return true; }

void UGearManagementComponent::OnSpaceHit_Implementation()
{
	if (!bSpaceBind) { return; }
	for (auto Actor : TacGears)
	{
		AGears* Gear = Cast<AGears>(Actor);
		Gear->OnSpaceHit(OwnerVehicle);
	}
}

bool UGearManagementComponent::OnShiftHit_Validate() { return true; }

void UGearManagementComponent::OnShiftHit_Implementation()
{
	if (!bShiftBind) { return; }
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

bool UGearManagementComponent::OnKeyQHit_Validate() { return true; }

void UGearManagementComponent::OnKeyQHit_Implementation()
{
	if (!bKeyQBind) { return; }
	for (auto Actor : TacGears)
	{
		AGears* Gear = Cast<AGears>(Actor);
		Gear->OnKeyQHit(OwnerVehicle);
	}
}

bool UGearManagementComponent::OnLClickHit_Validate(){ return true; }

void UGearManagementComponent::OnLClickHit_Implementation()
{
	if (!bLClickBind) { return; }
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

bool UGearManagementComponent::OnRClickHit_Validate() { return true; }

void UGearManagementComponent::OnRClickHit_Implementation()
{
	if (!bRClickBind) { return; }
	for (auto Actor : TacGears)
	{
		AGears* Gear = Cast<AGears>(Actor);
		Gear->OnRClickHit(OwnerVehicle);
	}
}

void UGearManagementComponent::JudgeBySocket(AGears* GearToJudge, int32 & Result)
{
	switch (GearToJudge->GearSocket)
	{
	case EGearSocket::ENull:
		Result = -1;
		break;
	case EGearSocket::EFront:
		if (bHasFront)
		{
			Result = -1; 
			break;
		}
		bHasFront = true;
		GearToJudge->OnPicked(GetOwner());
		/*UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetName());*/
		GearToJudge->AttachToActor(OwnerVehicle, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("EFront"));
		TacGears[0] = GearToJudge;
		Result = 0;
		BindKey(GearToJudge);
		break;
	case EGearSocket::EBack:
		if (bHasBack) 
		{ 
			Result = -1; 
			break;
		}
		bHasBack = true;
		GearToJudge->OnPicked(GetOwner());
		GearToJudge->AttachToActor(OwnerVehicle, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("EBack"));
		TacGears[1] = GearToJudge;
		Result = 1;
		BindKey(GearToJudge);
		break;
	case EGearSocket::ELeft:
		if (bHasLeft)
		{ 
			Result = -1;
			break;
		}
		bHasLeft = true;
		GearToJudge->OnPicked(GetOwner());
		GearToJudge->AttachToActor(OwnerVehicle, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("ELeft"));
		TacGears[2] = GearToJudge;
		Result = 2;
		BindKey(GearToJudge);
		break;
	case EGearSocket::ERight:
		if (bHasRight) 
		{ 
			Result = -1;
			break;
		}
		bHasRight = true;
		GearToJudge->OnPicked(GetOwner());
		GearToJudge->AttachToActor(OwnerVehicle, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("ERight"));
		TacGears[3] = GearToJudge;
		Result = 3;
		BindKey(GearToJudge);
		break;
	default:
		Result = -1;
		break;
	}
}

void UGearManagementComponent::BindKey(AGears * GearToBind)
{
	switch (GearToBind->GearBindKey)
	{
	case EGearBindKey::ENull:
		break;
	case EGearBindKey::EMouseLook:
		bMouseBind = true;
		UE_LOG(LogTemp, Warning, TEXT("Mouse bind"));
		break;
	case EGearBindKey::ELClick:
		bLClickBind = true;
		UE_LOG(LogTemp, Warning, TEXT("LClick bind"));
		break;
	case EGearBindKey::ERClick:
		bRClickBind = true;
		UE_LOG(LogTemp, Warning, TEXT("RClick bind"));
		break;
	case EGearBindKey::EShift:
		bShiftBind = true;
		UE_LOG(LogTemp, Warning, TEXT("Shift key bind"));
		break;
	case EGearBindKey::ESpace:
		bSpaceBind = true;
		UE_LOG(LogTemp, Warning, TEXT("Space key bind"));
		break;
	case EGearBindKey::EKeyQ:
		bKeyQBind = true;
		UE_LOG(LogTemp, Warning, TEXT("Q key bind"));
		break;
	default:
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

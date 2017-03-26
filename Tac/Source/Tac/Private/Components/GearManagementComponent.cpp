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

	// ...
	OwnerVehicle = Cast<ATacVehicle>(GetOwner());
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
	/*====================================
		Initialize here
	====================================*/
	OwnerPS = Cast<ATacPlayerState>(OwnerVehicle->PlayerState);


	/*====================================
		Bind input	
	====================================*/
	OwnerVehicle->InputComponent->BindAxis("LookUp", this, &UGearManagementComponent::OnLookUp);
	OwnerVehicle->InputComponent->BindAxis("LookRight", this, &UGearManagementComponent::OnLookRight);
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

void UGearManagementComponent::SpawnGear(TSubclassOf<AGears> GearToSet)
{
	/*
		auto Gear = NewObject<UGearComponent>(OwnerVehicle, GearToSet.GearComp);
		Gear->SetupAttachment(OwnerVehicle->GetRootComponent(), FName(*GearToSet.GetSocketName()));
		Gear->GetGearMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Gear->RegisterComponent();
	*/

}

void UGearManagementComponent::UpdateData(TSubclassOf<AGears> GearToAdd)
{
	OwnerPS->AddGear(GearToAdd);
}

void UGearManagementComponent::TryAddGear(TSubclassOf<AGears> GearToAdd)
{
	AGears* GearObj = Cast<AGears>(GearToAdd->GetDefaultObject());
	switch (GearObj->GearType)
	{
	case EGearType::EBoost:
		if (bShiftBind) { break; }
		bShiftBind = true;
		JudgeSocket(GearObj);
		break;
	case EGearType::EJump:
		if (bSpaceBind) { break; }
		bSpaceBind = true;
		JudgeSocket(GearObj);
		break;
	case EGearType::EProtector:
		JudgeSocket(GearObj);
		break;
	case EGearType::EShoot:
		if (bLClickBind) { break; }
		bLClickBind = true;
		JudgeSocket(GearObj);
		break;
	case EGearType::EThrow:
		if (bKeyQBind) { break; }
		bKeyQBind = true;
		JudgeSocket(GearObj);
		break;
	default:
		break;
	}
}

void UGearManagementComponent::OnLookUp(float val)
{
}

void UGearManagementComponent::OnLookRight(float val)
{
}

void UGearManagementComponent::OnSpaceHit()
{
}

void UGearManagementComponent::OnShiftHit()
{
}

void UGearManagementComponent::OnKeyQHit()
{
}

void UGearManagementComponent::JudgeSocket(AGears* GearToJudge)
{
	switch (GearToJudge->GearSocket)
	{
	case EGearSocket::ENull:
		break;
	case EGearSocket::ELeft:
		if (bHasLeft) { break; }
		bHasLeft = true;
		OwnerVehicle->GearActorLeft->SetChildActorClass(GearToJudge->StaticClass());
		OwnerVehicle->GearActorLeft->CreateChildActor();
		break;
	case EGearSocket::ERight:
		if (bHasRight) { break; }
		bHasRight = true;
		OwnerVehicle->GearActorRight->SetChildActorClass(GearToJudge->StaticClass());
		OwnerVehicle->GearActorRight->CreateChildActor();
		break;
	case EGearSocket::EFront:
		if (bHasFront) { break; }
		bHasFront = true;
		OwnerVehicle->GearActorFront->SetChildActorClass(GearToJudge->StaticClass());
		OwnerVehicle->GearActorFront->CreateChildActor();
		break;
	case EGearSocket::EBack:
		if (bHasBack) { break; }
		bHasBack = true;
		OwnerVehicle->GearActorBack->SetChildActorClass(GearToJudge->StaticClass());
		OwnerVehicle->GearActorBack->CreateChildActor();
		break;
	default:
		break;
	}
}

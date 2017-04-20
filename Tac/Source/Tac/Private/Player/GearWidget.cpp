// Copyright by GameDream.

#include "Tac.h"
#include "UnrealNetwork.h"
#include "GearWidget.h"

/*
UGearWidget::UGearWidget()
{
bReplicates = true;
}
*/


void UGearWidget::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME(UGearWidget, TacController);
}

FObjectReplicatorBase * UGearWidget::InstantiateReplicatorForSubObject(UClass * SubobjClass)
{
	return nullptr;
}

bool UGearWidget::ReplicateSubobjects(UActorChannel * Channel, FOutBunch * Bunch, FReplicationFlags * RepFlags)
{
	return true;
}

void UGearWidget::OnSubobjectCreatedFromReplication(UObject * NewSubobject)
{
}

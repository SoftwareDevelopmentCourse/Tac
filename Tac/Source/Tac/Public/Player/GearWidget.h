// Copyright by GameDream.

#pragma once

#include "Blueprint/UserWidget.h"
#include "GearWidget.generated.h"

/**
 * 
 */
UCLASS()
class TAC_API UGearWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//UGearWidget();
	UFUNCTION(BlueprintImplementableEvent, Category = "Gear")
	void AddGearSlot();
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Gear")
	class ATacController* TacController;
	
	/** FActory method for instantiating templatized TobjectReplicator class for subobject replication */
	virtual class FObjectReplicatorBase * InstantiateReplicatorForSubObject(UClass *SubobjClass);

	/** Method that allows an Actor to replicate subobjects on its Actor channel */
	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags);

	/** Called on the Actor when a new subobject is dynamically created via replication */
	virtual void OnSubobjectCreatedFromReplication(UObject *NewSubobject);

	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}
};

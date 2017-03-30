// Copyright by GameDream.

#pragma once

#include "GameFramework/Actor.h"
#include "TacHeader.h"
#include "Gears.generated.h"

class ATacVehicle;

UCLASS()
class TAC_API AGears : public AActor
{
	GENERATED_BODY()

	/** Root component of gear */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gear, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root; // TODO Sometimes should be replaced by skeletal mesh

public:	
	// Sets default values for this actor's properties
	AGears();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	/** Gear hover's range */
	UPROPERTY(Category = GearWorld, EditAnywhere)
	float FloatRange;
	
	/** Gear spawn's rate, amount per min */
	UPROPERTY(Category = GearWorld, EditAnywhere)
	int32 SpawnRate;

	/** Gear's maximum existence at base */
	UPROPERTY(Category = GearWorld, EditAnywhere)
	int32 MaxExistenceBase;

	/** Gear's maximum existence outdoors */
	UPROPERTY(Category = GearWorld, EditAnywhere)
	int32 MaxExistenceOutdoors;

	/** Gear's cost at base */
	UPROPERTY(Category = GearWorld, EditAnywhere)
	int32 CostBase;

	/** Gear's cost outdoors */
	UPROPERTY(Category = GearWorld, EditAnywhere)
	int32 CostOutdoors;

	/** Gear's installation socket */
	UPROPERTY(Category = GearVehicle, EditAnywhere)
	EGearSocket GearSocket;

	/** Gear's installation type */
	UPROPERTY(Category = GearVehicle, EditAnywhere)
	EGearType GearType;

	/** Gear's name for display */
	UPROPERTY(Category = GearVehicle, EditAnywhere)
	FName GearName;

public:
	/** When mouse move up */
	virtual void OnLookUp(float val);
	/** When mouse move right */
	virtual void OnLookRight(float val);
	/** When hitting spacebar */
	virtual void OnSpaceHit();
	/** When hitting left shift */
	virtual void OnShiftHit();
	/** When hitting key Q */
	virtual void OnKeyQHit();
	/** When hitting left mouse button */
	virtual void OnLClickHit();
	/** When hitting right mouse button */
	virtual void OnRClickHit();

public:
	/** Called by timeline, neet UFUNCTION() */
	UFUNCTION()
	void GearsHover(float val);

	/**  When gear is being spawned on the world */
	void WorldSpawn();

	/** Curve of gear's hover */
	class UCurveFloat* TimelineCurve;

	/** Uses timeline component to control curve */
	class UTimelineComponent* Timeline;

	/** Timeline triggered function */
	FOnTimelineFloat InterpFunction{};

private:
	/** Add gears rotation */
	void AddGearRotation();
	
	/** Whether the gear is picked up */
	bool bShouldRotate;

	ATacVehicle* OwnerVehicle;
};

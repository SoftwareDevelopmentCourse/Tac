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

public:	
	// Sets default values for this actor's properties
	AGears();
	/** Root component of gear */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gear, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root; // TODO Sometimes should be replaced by skeletal mesh

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(Replicated)
	bool bPicked = false;

	AActor * OwnerActor;

public:
	/** Gear hover's range */
	UPROPERTY(Replicated, Category = GearWorld, EditAnywhere)
	float FloatRange;
	
	/** Gear spawn's rate, amount per min */
	UPROPERTY(Replicated, Category = GearWorld, EditAnywhere)
	int32 SpawnRate;

	/** Gear's maximum existence at base */
	UPROPERTY(Replicated, Category = GearWorld, EditAnywhere)
	int32 MaxExistenceBase;

	/** Gear's maximum existence outdoors */
	UPROPERTY(Replicated, Category = GearWorld, EditAnywhere)
	int32 MaxExistenceOutdoors;

	/** Gear's cost at base */
	UPROPERTY(Replicated, Category = GearWorld, EditAnywhere)
	int32 CostBase;

	/** Gear's cost outdoors */
	UPROPERTY(Replicated, Category = GearWorld, EditAnywhere)
	int32 CostOutdoors;

	/** Gear's installation socket */
	UPROPERTY(Replicated, Category = GearVehicle, EditAnywhere)
	EGearSocket GearSocket;

	UPROPERTY(Replicated, Category = GearVehicle, EditAnywhere)
	EGearBindKey GearBindKey;

	/** Gear's name for display */
	UPROPERTY(Replicated, Category = GearVehicle, EditAnywhere)
	FName GearName;

public:
	/** When mouse move up */
	virtual void OnLookUp(float val);
	/** When mouse move right */
	virtual void OnLookRight(float val);
	/** When hitting spacebar */
	virtual void OnSpaceHit(AActor* Target);
	/** When hitting left shift */
	virtual void OnShiftHit(AActor* Target);
	/** When hitting key Q */
	virtual void OnKeyQHit(AActor* Target);
	/** When hitting left mouse button */
	virtual void OnLClickHit(AActor* Target);
	/** When hitting right mouse button */
	virtual void OnRClickHit(AActor* Target);

public:
	/** Called by timeline, neet UFUNCTION() */
	UFUNCTION()
	void GearsHover(float val);

	/**  When gear is being spawned on the world */
	void WorldSpawn();

	/** When gear is picked up */
	void OnPicked(AActor* Owner);

	/** Curve of gear's hover */
	class UCurveFloat* TimelineCurve;

	/** Uses timeline component to control curve */
	class UTimelineComponent* Timeline;

	/** Timeline triggered function */
	FOnTimelineFloat InterpFunction{};

	UFUNCTION(Server, Reliable, WithValidation)
	void ResetLocation();

private:
	/** Add gears rotation */
	void AddGearRotation();

};

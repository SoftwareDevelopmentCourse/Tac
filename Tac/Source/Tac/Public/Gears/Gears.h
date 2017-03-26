// Copyright by GameDream.

#pragma once

#include "GameFramework/Actor.h"
#include "TacHeader.h"
#include "Gears.generated.h"

UCLASS()
class TAC_API AGears : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gear, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GearMesh;


public:	
	// Sets default values for this actor's properties
	AGears();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UCurveFloat* TimelineCurve;

	class UTimelineComponent* Timeline;

	FOnTimelineFloat InterpFunction{};


public:
	/** Gear hover's range */
	UPROPERTY(Category = Gear, EditAnywhere)
	float FloatRange;
	
	/** Gear spawn's rate, amount per min */
	UPROPERTY(Category = Gear, EditAnywhere)
	int32 SpawnRate;

	UPROPERTY(Category = Gear, EditAnywhere)
	EGearSocket GearSocket;

	UPROPERTY(Category = Gear, EditAnywhere)
	EGearType GearType;

	UPROPERTY(Category = Gear, EditAnywhere)
	FName GearName;

	/** Gear's maximum existence at base */
	UPROPERTY(Category = Gear, EditAnywhere)
	int32 MaxExistenceBase;

	/** Gear's maximum existence outdoors */
	UPROPERTY(Category = Gear, EditAnywhere)
	int32 MaxExistenceOutdoors;

	/** Gear's cost at base */
	UPROPERTY(Category = Gear, EditAnywhere)
	int32 CostBase;

	/** Gear's cost outdoors */
	UPROPERTY(Category = Gear, EditAnywhere)
	int32 CostOutdoors;

public:
	/** Called by timeline, neet UFUNCTION() */
	UFUNCTION()
	void GearsHover(float val);
	
	/** When gear is being picked up */
	void OnPickedup();


private:
	/** Add gears rotation */
	void AddGearRotation();
	
	/** Whether the gear is picked up */
	bool bPickedup;
};

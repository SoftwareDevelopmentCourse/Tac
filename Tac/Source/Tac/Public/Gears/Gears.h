// Copyright by GameDream.

#pragma once

#include "GameFramework/Actor.h"
#include "TacHeader.h"
#include "Gears.generated.h"

class UGearComponent;

UCLASS()
class TAC_API AGears : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gear, meta = (AllowPrivateAccess = "true"))
	UGearComponent* GearComp;


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

	/** Gear's struct */
	UPROPERTY(Category = Gear, EditAnywhere)
	FGear Gear;

public:
	/** Called by timeline, neet UFUNCTION() */
	UFUNCTION()
	void GearsHover(float val);
	
	/** When gear is being picked up */
	void OnPickedup();

	/** Return gear component that gear using */
	FORCEINLINE UGearComponent* GetGearComp() const { return GearComp; }

private:
	/** Add gears rotation */
	void AddGearRotation();
	
	/** Whether the gear is picked up */
	bool bPickedup;
};

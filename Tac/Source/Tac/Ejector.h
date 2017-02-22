// Copyright by GameDream.

#pragma once

#include "GameFramework/Actor.h"
#include "Ejector.generated.h"

UCLASS()
class TAC_API AEjector : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gear, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Ejector;

public:	
	// Sets default values for this actor's properties
	AEjector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UCurveFloat* TimelineCurve;

	class UTimelineComponent* Timeline;

	FOnTimelineFloat InterpFunction{};
	UFUNCTION()
	void EjectorFloat(float val);

	UPROPERTY(Category = Gear, EditAnywhere)
	float FloatRange;
	
};

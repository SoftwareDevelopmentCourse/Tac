// Copyright by GameDream.

#pragma once

#include "GameFramework/Actor.h"
#include "Gas.generated.h"

UCLASS()
class TAC_API AGas : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = Setup)
	UStaticMeshComponent* GasMesh;
	UPROPERTY(VisibleAnywhere, Category = Setup)
	UBoxComponent* RangeBox;
public:	
	// Sets default values for this actor's properties
	AGas();

	UFUNCTION()
	void OverlapperSave(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	
	
};

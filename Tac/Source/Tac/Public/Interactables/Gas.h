// Copyright by GameDream.

#pragma once

#include "GameFramework/Actor.h"
#include "Gas.generated.h"

UCLASS()
class TAC_API AGas : public AActor
{
	GENERATED_BODY()

	/** Gas mesh */
	UPROPERTY(VisibleAnywhere, Category = Setup)
	UStaticMeshComponent* GasMesh;
	/** Gas interaction volume */
	UPROPERTY(VisibleAnywhere, Category = Setup)
	UBoxComponent* RangeBox;
public:	
	// Sets default values for this actor's properties
	AGas();

	/** Save game for player overlapping volume */
	UFUNCTION()
	void OverlapperSave(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};

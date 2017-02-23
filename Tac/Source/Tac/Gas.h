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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	
	
};

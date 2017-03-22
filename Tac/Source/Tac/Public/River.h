// Copyright by GameDream.

#pragma once

#include "GameFramework/Actor.h"
#include "River.generated.h"

UCLASS()
class TAC_API ARiver : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARiver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};

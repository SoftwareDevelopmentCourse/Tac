// Copyright by GameDream.

#include "Tac.h"
#include "River.h"


// Sets default values
ARiver::ARiver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARiver::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


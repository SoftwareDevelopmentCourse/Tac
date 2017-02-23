// Copyright by GameDream.

#include "Tac.h"
#include "Gas.h"


// Sets default values
AGas::AGas()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GasMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GasMesh"));
	RootComponent = GasMesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Geometry/SM_Gas.SM_Gas'"));
	if (Mesh.Object)
	{
		GasMesh->SetStaticMesh(Mesh.Object);
	}
	GasMesh->SetMobility(EComponentMobility::Static);

	RangeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RangeBox"));
	RangeBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGas::BeginPlay()
{
	Super::BeginPlay();
	
}



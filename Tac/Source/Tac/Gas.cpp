// Copyright by GameDream.

#include "Tac.h"
#include "Gas.h"
#include "TacController.h"

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
	RootComponent->SetMobility(EComponentMobility::Static);

	RangeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RangeBox"));
	RangeBox->SetupAttachment(RootComponent);
	RangeBox->SetRelativeLocation(FVector(310.f, 0.f, 100.f));
	RangeBox->SetBoxExtent(FVector(850.f, 1200.f, 130.f));
	RangeBox->SetMobility(EComponentMobility::Static);
	RangeBox->OnComponentBeginOverlap.AddDynamic(this, &AGas::OverlapperSave);
}

// Called when the game starts or when spawned
void AGas::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGas::OverlapperSave(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ATacController* OverlapController = Cast<ATacController>(OtherActor->GetInstigatorController());
	OverlapController->SaveGame();
	UE_LOG(LogTemp, Warning, TEXT("Gas save"));	
}
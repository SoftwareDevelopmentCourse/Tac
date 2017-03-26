// Copyright by GameDream.

#pragma once

#include "Components/ActorComponent.h"
#include "GearComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TAC_API UGearComponent : public USceneComponent
{
	GENERATED_BODY()


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gear, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GearMesh;

public:	
	// Sets default values for this component's properties
	UGearComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE UStaticMeshComponent* GetGearMesh() const { return GearMesh; }
	
};

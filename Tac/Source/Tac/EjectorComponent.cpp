// Copyright by GameDream.

#include "Tac.h"
#include "EjectorComponent.h"

UEjectorComponent::UEjectorComponent()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EjectorMesh(TEXT("/Game/Geometry/SM_Ejector"));
	SetStaticMesh(EjectorMesh.Object);
}



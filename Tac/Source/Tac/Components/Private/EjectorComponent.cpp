// Copyright by GameDream.

#include "Tac.h"
#include "Components/Public/EjectorComponent.h"

UEjectorComponent::UEjectorComponent()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EjectorMesh(TEXT("StaticMesh'/Game/Tac/Art/Gears/SM_Ejector.SM_Ejector'"));
	SetStaticMesh(EjectorMesh.Object);
}



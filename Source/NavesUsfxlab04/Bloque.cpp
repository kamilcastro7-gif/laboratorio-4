#include "Bloque.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

ABloque::ABloque()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshBloque = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshBloque"));
	RootComponent = MeshBloque;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CuboAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (CuboAsset.Succeeded())
	{
		MeshBloque->SetStaticMesh(CuboAsset.Object);
	}
}

void ABloque::BeginPlay()
{
	// Llama a la base de AActor correctamente
	Super::BeginPlay();
}

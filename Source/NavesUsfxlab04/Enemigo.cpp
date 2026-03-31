#include "Enemigo.h"
#include "Bloque.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

AEnemigo::AEnemigo()
{
	PrimaryActorTick.bCanEverTick = true;

	MallaDona = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaDona"));
	RootComponent = MallaDona;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TorusMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Torus.Shape_Torus'"));
	if (TorusMesh.Succeeded())
	{
		MallaDona->SetStaticMesh(TorusMesh.Object);
	}

	Velocidad = 450.0f;
	DireccionMovimiento = FVector(1.0f, 1.0f, 0.0f).GetSafeNormal();

	// Inicializamos contadores
	RebotesTotales = 0;
	LimiteRebotes = 20;
}

void AEnemigo::BeginPlay()
{
	Super::BeginPlay();
	// Guardamos donde nació la dona para el respawn
	SpawnLocation = GetActorLocation();
}

void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector ActualLocation = GetActorLocation();
	FVector NuevaPosicion = ActualLocation + (DireccionMovimiento * Velocidad * DeltaTime);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, ActualLocation, NuevaPosicion, ECC_WorldStatic, Params))
	{
		// Aumentar contador de rebotes
		RebotesTotales++;

		// Verificar si ya llegó al límite
		if (RebotesTotales >= LimiteRebotes)
		{
			SetActorLocation(SpawnLocation); // Vuelve a su spawn
			RebotesTotales = 0;             // Reinicia el contador
			// Opcional: puedes darle una dirección aleatoria aquí
		}
		else
		{
			DireccionMovimiento = DireccionMovimiento.MirrorByVector(Hit.Normal);
			SetActorLocation(Hit.Location + (Hit.Normal * 15.0f));
		}
	}
	else
	{
		SetActorLocation(NuevaPosicion);
	}
}
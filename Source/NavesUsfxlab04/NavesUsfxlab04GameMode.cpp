#include "NavesUsfxlab04GameMode.h"
#include "Bloque.h"
#include "Enemigo.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

ANavesUsfxlab04GameMode::ANavesUsfxlab04GameMode()
{
}

void ANavesUsfxlab04GameMode::BeginPlay()
{
	Super::BeginPlay();

	// --- 1. GENERACIÓN DEL DISEÑO EN LA TLISTA ---

	// A. BORDES DEL ESTADIO (12x10)
	for (int fila = 0; fila < 12; fila++)
	{
		for (int col = 0; col < 10; col++)
		{
			bool esBorde = (fila == 0 || fila == 11 || col == 0 || col == 9);
			bool esEntrada = (fila == 0 && (col == 4 || col == 5));

			if (esBorde && !esEntrada)
			{
				float PosX = -600.0f + (fila * 100.0f);
				float PosY = -450.0f + (col * 100.0f);
				ListaCamino.Agregar(FVector(PosX, PosY, 100.0f));
			}
		}
	}

	// B. 9 BLOQUES INTERNOS (Dispersos)
	float PuntosInternosX[] = { -350.0f, -350.0f, 0.0f, 0.0f, 350.0f, 350.0f, -150.0f, 150.0f, 10.0f };
	float PuntosInternosY[] = { -250.0f, 250.0f, -300.0f, 300.0f, -250.0f, 250.0f, 0.0f, 0.0f, -100.0f };

	for (int i = 0; i < 9; i++)
	{
		ListaCamino.Agregar(FVector(PuntosInternosX[i], PuntosInternosY[i], 100.0f));
	}

	// --- 2. SPAWN RECORRIENDO EL TEMPLATE ---
	Nodo<FVector>* Actual = ListaCamino.Cabeza;
	int ID = 0;

	while (Actual)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Name = FName(*FString::Printf(TEXT("Bloque_Final_V5_%d"), ID));
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ABloque* NuevoBloque = GetWorld()->SpawnActor<ABloque>(ABloque::StaticClass(), Actual->Dato, FRotator::ZeroRotator, SpawnParams);

		if (NuevoBloque)
		{
			NuevoBloque->SetActorScale3D(FVector(1.0f, 1.0f, 2.0f));
			ID++;
		}
		Actual = Actual->Siguiente;
	}

	// --- 3. SPAWN DE LA DONA (PARCHE DE SEGURIDAD) ---

	// La ponemos en el centro (0,0) y un poco elevada (Z=200) para evitar colisiones iniciales
	FVector UbicacionDona = FVector(0.0f, 0.0f, 200.0f);

	FActorSpawnParameters DonaParams;
	// Esto obliga a la dona a aparecer aunque toque algo
	DonaParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AEnemigo* DonaActor = GetWorld()->SpawnActor<AEnemigo>(AEnemigo::StaticClass(), UbicacionDona, FRotator::ZeroRotator, DonaParams);

	if (GEngine && DonaActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("¡DONA SPAWNEADA EXITOSAMENTE!"));
	}
}
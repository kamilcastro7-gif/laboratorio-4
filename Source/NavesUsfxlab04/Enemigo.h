#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Enemigo.generated.h"

UCLASS()
class NAVESUSFXLAB04_API AEnemigo : public AActor
{
	GENERATED_BODY()

public:
	AEnemigo();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visual")
	UStaticMeshComponent* MallaDona;

	UPROPERTY(EditAnywhere, Category = "Movimiento")
	float Velocidad;

	UPROPERTY(EditAnywhere, Category = "Movimiento")
	FVector DireccionMovimiento;

	// --- NUEVO: Lógica de Spawn y Contador ---
	FVector SpawnLocation;
	int32 RebotesTotales;
	int32 LimiteRebotes;
};
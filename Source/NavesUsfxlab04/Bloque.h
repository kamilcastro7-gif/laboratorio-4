#pragma once

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bloque.generated.h"

UCLASS()
class NAVESUSFXLAB04_API ABloque : public AActor
{
	GENERATED_BODY()

public:
	ABloque();

protected:
	// Firma corregida para evitar errores de Super
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bloque")
	class UStaticMeshComponent* MeshBloque;
};
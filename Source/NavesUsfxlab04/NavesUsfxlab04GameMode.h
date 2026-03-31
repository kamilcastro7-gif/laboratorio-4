#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NavesUsfxlab04GameMode.generated.h"

// --- ESTRUCTURA DE DATOS: LISTA TEMPLATE ---
template <typename T>
class Nodo {
public:
	T Dato;
	Nodo<T>* Siguiente;
	Nodo(T _Dato) : Dato(_Dato), Siguiente(nullptr) {}
};

template <typename T>
class TLista {
public:
	Nodo<T>* Cabeza;
	TLista() : Cabeza(nullptr) {}

	void Agregar(T Valor) {
		Nodo<T>* Nuevo = new Nodo<T>(Valor);
		if (!Cabeza) {
			Cabeza = Nuevo;
		}
		else {
			Nodo<T>* Aux = Cabeza;
			while (Aux->Siguiente) {
				Aux = Aux->Siguiente;
			}
			Aux->Siguiente = Nuevo;
		}
	}

	~TLista() {
		Nodo<T>* Act = Cabeza;
		while (Act) {
			Nodo<T>* Sig = Act->Siguiente;
			delete Act;
			Act = Sig;
		}
	}
};

UCLASS()
class NAVESUSFXLAB04_API ANavesUsfxlab04GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANavesUsfxlab04GameMode();

protected:
	virtual void BeginPlay() override;

private:
	// Lista de posiciones para el escenario
	TLista<FVector> ListaCamino;
};

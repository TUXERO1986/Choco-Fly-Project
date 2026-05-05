#pragma once
#include "ControladorArchivos.h"
class ControladorPaquetes {
private:
	Lista<Paquete*>* paquetes;
	ControladorArchivos* controladorArchivos;
public:
	ControladorPaquetes();
	~ControladorPaquetes();
	void GenerarPaquetes(int contador, Lista<Hotel*>* listhoteles, Lista<Vuelo*>* listvuelos);
	void AgregarNuevoPaquete(Vuelo* vuelo, Hotel* hotel);
	void MostrarPaquetes();
	Lista<Paquete*>* getPaquetes();
	void setPaquetes(Lista<Paquete*>* paquetes);
};


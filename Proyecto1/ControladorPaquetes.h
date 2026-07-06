#pragma once
#include "ControladorArchivos.h"
#include "ArbolAVLMiltiClave.h"
#include "ArbolAVL.h"
class ControladorPaquetes {
private:
	Lista<Paquete*>* paquetes;
	ArbolAVL<Paquete*>* paquetesMenorPrecio;
	ArbolAVLMultiClave<Paquete*, string>* indicePorDestino;
	ControladorArchivos* controladorArchivos;
public:
	ControladorPaquetes();
	~ControladorPaquetes();
	void MostrarPaquetesCiudades(string ciudadOrigen, string ciudadDestino);
	void GenerarPaquetes(int contador, Lista<Hotel*>* listhoteles, Lista<Vuelo*>* listvuelos);
	void AgregarNuevoPaquete(Vuelo* vueloIda, Hotel* hotel);
	void MostrarPaquetes();
	Lista<Paquete*>* getPaquetes();
	ArbolAVL<Paquete*>* getPaquetesMenorPrecio();
	ArbolAVLMultiClave<Paquete*, string>* getIndicePorDestino();
	void setPaquetes(Lista<Paquete*>* paquetes);
};


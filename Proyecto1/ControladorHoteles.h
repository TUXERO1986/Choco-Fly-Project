#pragma once

#include "ControladorArchivos.h"
#include "ArbolAVL.h"
#include "ArbolAVLMiltiClave.h"
class ControladorHoteles
{
private:
	Lista<Hotel*>* hoteles;
	ArbolAVL<Hotel*>* hotelesMenorPrecio;
	ArbolAVLMultiClave<Hotel*, string>* indicePorCiudad;
	ControladorArchivos* controladorArchivos;
public:
	ControladorHoteles();
	~ControladorHoteles();
	void GenerarHoteles(int contador, Lista<CiudadID*>* listaCiudades);
	void AgregarNuevoHotel(string nombre, string ciudad, float puntuacion, float precioNoche);
	void MostrarHoteles();
	Lista<Hotel*>* getHotelesPorCiudad(string ciudad);
	Lista<Hotel*>* getHoteles();
	ArbolAVL<Hotel*>* getHotelesMenorPrecio();
};


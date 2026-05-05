#pragma once

#include "ControladorArchivos.h"
class ControladorHoteles
{
private:
	Lista<Hotel*>* hoteles;
	ControladorArchivos* controladorArchivos;
public:
	ControladorHoteles();
	~ControladorHoteles();
	void GenerarHoteles(int contador, Lista<CiudadID*>* listaCiudades);
	void AgregarNuevoHotel(string nombre, string ciudad, float puntuacion, float precioNoche);
	void MostrarHoteles();
	Lista<Hotel*>* getHoteles();
};


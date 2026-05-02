#pragma once
#include <iostream>
using namespace std;
class Ruta
{
private:
	string origen;
	string destino;
	float distancia;
public:
	Ruta();
	Ruta(string, string, float);
	string getOrigen();
	string getDestino();
	float getDistancia();

	void setOrigen(string);
	void setDestino(string);
	void setDistancia(float);

	void MostrarDatos();
};


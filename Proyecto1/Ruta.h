#pragma once
#include <iostream>
using namespace std;
class Ruta
{
private:
	string origen;
	string destino;
	string aerolinea;
	float precio;
	float distancia;
public:
	Ruta();
	Ruta(string, string, string, float, float);
	string getOrigen();
	string getDestino();
	string getAerolinea();
	float getPrecio();
	float getDistancia();

	void setOrigen(string);
	void setDestino(string);
	void setAerolinea(string);
	void setPrecio(float);
	void setDistancia(float);

	void MostrarDatos();
};


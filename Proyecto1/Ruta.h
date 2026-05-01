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
	string getAerolinea();
	float getPrecio();
	float getDistancia();
	string getFecha();

	void setOrigen(string);
	void setDestino(string);
	void setAerolinea(string);
	void setPrecio(float);
	void setDistancia(float);
	void setFecha(string fecha);

	void MostrarDatos();
};


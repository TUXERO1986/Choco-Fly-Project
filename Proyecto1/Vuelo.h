#pragma once
#include "ControladorAsientos.h"
class Vuelo
{
private:
	ControladorAsientos* controladorAsientos;
	string origen;
	string destino;
	string escalas;
	string fecha;
	float distancia;
public:
	Vuelo(string o, string d, string e, string f, float distancia,ControladorAsientos* controladorAsientos);

	void MostrarVuelo();
	void MostrarAsientos();
	string GetFechaPorDestinoYOrigen(string origen,string destino);

	string getOrigen();
	string getDestino();
	string getEscalas();
	string getFecha();
	float getDistancia();
	ControladorAsientos* getControladorAsientos();

	void setOrigen(string o);
	void setDestino(string d);
	void setEscalas(string e);
	void setFecha(string f);
	void setDistancia(float distancia);	

};
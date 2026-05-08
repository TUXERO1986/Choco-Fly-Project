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
	float precio;
public:
	Vuelo(string o, string d, string e, string f, float distancia,float p);

	void MostrarVuelo();
	void MostrarAsientos();
	string GetFechaPorDestinoYOrigen(string origen,string destino);

	string getOrigen();
	string getDestino();
	string getEscalas();
	string getFecha();
	float getPrecio();
	float getDistancia();
	void setOrigen(string o);
	void setDestino(string d);
	void setEscalas(string e);
	void setFecha(string f);
	void setPrecio(float p);
	void setDistancia(float distancia);	

};
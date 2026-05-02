#pragma once
#include <iostream>
using namespace std;
class Vuelo
{
private:
	string origen;
	string destino;
	string escalas;
	string fecha;
	float precio;
public:
	Vuelo(string o, string d, string e, string f, float p);

	void MostrarVuelo();
	string GetFechaPorDestinoYOrigen(string origen,string destino);

	string getOrigen();
	string getDestino();
	string getEscalas();
	string getFecha();
	float getPrecio();
	
	void setOrigen(string o);
	void setDestino(string d);
	void setEscalas(string e);
	void setFecha(string f);
	void setPrecio(float p);

};


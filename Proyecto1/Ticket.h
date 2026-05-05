#pragma once
#include <iostream>
#include <string>
using namespace std;
class Ticket
{
private:
	string nombre;
	string origen;
	string destino;
	string escalas;
	float precio;
	float distancia;
	int equipaje;
	int equipajecabina;
public:
	Ticket();
	Ticket(string nombre,string origen, string destino, string escalas, float precio, float distancia, int equipaje, int equipajecabina);
	void MostrarTicket();
	string getNombre();
	string getOrigen();
	string getDestino();
	string getEscalas();
	float getPrecio();
	float getDistancia();
	int getEquipaje();
	int getEquipajeCabina();
	void setOrigen(string origen);
	void setDestino(string destino);
	void setEscalas(string escalas);
	void setPrecio(float precio);
	void setDistancia(float distancia);
	void setEquipaje(int equipaje);
	void setEquipajeCabina(int equipajecabina);
	void setNombre(string nombre);
};


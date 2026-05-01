#pragma once+
#include <iostream>
#include <string>
using namespace std;
class Ticket
{
private:
	string origen;
	string destino;
	string escalas;
	float precio;
	int equipaje;
	int equipajecabina;
public:
	Ticket();
	Ticket(string origen,string destino,float precio,int equipaje,int equipajecabina);
	void MostrarTicket();
	string getOrigen();
	string getDestino();
	float getPrecio();
	int getEquipaje();
	int getEquipajeCabina();
	void setOrigen(string origen);
	void setDestino(string destino);
	void setPrecio(float precio);
	void setEquipaje(int equipaje);
	void setEquipajeCabina(int equipajecabina);
};


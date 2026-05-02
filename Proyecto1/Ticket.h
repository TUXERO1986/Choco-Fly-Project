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
	string fecha;
	float distancia;
	float precio;
	int equipaje;
	int equipajecabina;
public:
	Ticket();
	Ticket(string origen,string destino,string fecha,float precio,int equipaje,int equipajecabina,float distancia);
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


#pragma once
#include "Reserva.h"
class Ticket : public Reserva
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
	Ticket(string codigoUsuario,string nombreUsuario,string origen, string destino, string escalas, 
		float precio, float distancia, int equipaje, int equipajecabina);
	void MostrarReserva() override;
	string aTextoArchivo() override;
	string getNombre();
	string getOrigen();
	string getDestino();
	string getEscalas();
	float getPrecio();
	float getPrecioTotal() override;
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


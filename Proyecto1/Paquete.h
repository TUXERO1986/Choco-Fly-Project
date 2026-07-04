#pragma once
#include "Hotel.h"
#include "Vuelo.h"
class Paquete : public Servicio
{
private:
	Vuelo* vueloIncluido;
	Hotel* hotelIncluido;
	int id;
public:
	Paquete(Vuelo* vuelo, Hotel* hotel,int id);
	void MostrarDatos();
	Vuelo* getVueloIncluido();
	Hotel* getHotelIncluido();
	string aTextoArchivo();
	void setVueloIncluido(Vuelo* vuelo);
	void setHotelIncluido(Hotel* hotel);
	int getId();
};


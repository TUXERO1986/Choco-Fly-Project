#pragma once
#include "Hotel.h"
#include "Vuelo.h"
class Paquete
{
private:
	Vuelo* vueloIncluido;
	Hotel* hotelIncluido;
	int id;
public:
	Paquete(Vuelo* vuelo, Hotel* hotel,int id);
	void MostrarPaquete();
	Vuelo* getVueloIncluido();
	Hotel* getHotelIncluido();
	void setVueloIncluido(Vuelo* vuelo);
	void setHotelIncluido(Hotel* hotel);
	float getPrecioBase();
	int getId();
};


#pragma once
#include <iostream>
using namespace std;
class Hotel
{
private:
	string nombre;
	string ciudad;
	float puntuacion;;
	float precioNoche;
public:
	Hotel(string nombre, string ciudad, float puntuacion, float precioNoche);
	void MostrarHotel();
	string getNombre();
	string getCiudad();
	float getPuntuacion();
	float getPrecioNoche();
	void setNombre(string nombre);
	void setCiudad(string ciudad);
	void setPuntuacion(float puntuacion);
	void setPrecioNoche(float precioNoche);
};


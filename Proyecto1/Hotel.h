#pragma once
#include "ControladorHabitaciones.h"
class Hotel
{
private:
	string nombre;
	string ciudad;
	float puntuacion;;
	float precioNoche;
	int id;
	ControladorHabitaciones* controladorHabitaciones;
public:
	Hotel(string nombre, string ciudad, float puntuacion, float precioNoche,ControladorHabitaciones* controladorHabitaciones,int id);
	void MostrarHotel();
	void MostrarHabitaciones();
	string getNombre();
	string getCiudad();
	int getId();
	float getPuntuacion();
	float getPrecioNoche();
	ControladorHabitaciones* getControladorHabitaciones();
	void setNombre(string nombre);
	void setCiudad(string ciudad);
	void setPuntuacion(float puntuacion);
	void setPrecioNoche(float precioNoche);
};


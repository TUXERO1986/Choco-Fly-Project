#pragma once
#include "Habitacion.h"
#include "Lista.h"
class Hotel
{
private:
	string nombre;
	string ciudad;
	float puntuacion;;
	float precioNoche;
	int id;
	Lista<Habitacion*>* habitaciones;
public:
	Hotel(string nombre, string ciudad, float puntuacion, float precioNoche,int id);
	void MostrarHotel();
	void MostrarHabitaciones();
	string getNombre();
	string getCiudad();
	int getId();
	float getPuntuacion();
	float getPrecioNoche();
	void setNombre(string nombre);
	void setCiudad(string ciudad);
	void setPuntuacion(float puntuacion);
	void setPrecioNoche(float precioNoche);
	void GenerarHabitaciones();
	bool verificarHabitacion(int numeroHabitacion);
	string ObtenerEstadoHabitacionesString();
	void CargarEstadoHabitacionesString(string estado);
	Lista<Habitacion*>* getHabitaciones();
	void setHabitaciones(Lista<Habitacion*>* asientos);
};


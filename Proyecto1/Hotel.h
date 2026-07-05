#pragma once
#include "Servicio.h"
#include "Habitacion.h"
#include "Lista.h"
class Hotel : public Servicio
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
	void MostrarDatos();
	void MostrarHabitaciones();
	string getNombre();
	string getCiudad();
	int getId();
	float getPuntuacion();
	void setNombre(string nombre);
	void setCiudad(string ciudad);
	void setPuntuacion(float puntuacion);
	void setPrecioNoche(float precioNoche);
	void GenerarHabitaciones();
	bool verificarHabitacion(int numeroHabitacion);
	string ObtenerEstadoHabitacionesString();
	string aTextoArchivo();
	void CargarEstadoHabitacionesString(string estado);
	Lista<Habitacion*>* getHabitaciones();
	void setHabitaciones(Lista<Habitacion*>* asientos);
};


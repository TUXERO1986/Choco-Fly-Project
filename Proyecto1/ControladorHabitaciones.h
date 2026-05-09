#pragma once
#include "Habitacion.h"
#include "Lista.h"
class ControladorHabitaciones
{
private:
	Lista<Habitacion*>* habitaciones;
public:
	ControladorHabitaciones();
	void MostrarHabitaciones();
	void GenerarHabitaciones();
	bool verificarHabitacion(int numeroHabitacion);
	string ObtenerEstadoHabitacionesString();
	void CargarEstadoHabitacionesString(string estado);
	Lista<Habitacion*>* getHabitaciones();
	void setHabitaciones(Lista<Habitacion*>* asientos);
};


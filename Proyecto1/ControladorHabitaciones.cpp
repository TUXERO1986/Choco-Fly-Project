#include "ControladorHabitaciones.h"
ControladorHabitaciones::ControladorHabitaciones() {
	this->habitaciones = new Lista<Habitacion*>();
	GenerarHabitaciones();
}
void ControladorHabitaciones::MostrarHabitaciones() {
	for (int i = 0; i < habitaciones->longitud(); i++) {
		Habitacion* aux = habitaciones->obtenerPos(i);
		aux->MostrarHabitacion();
		cout << " ";
		if ((i + 1) % 6 == 0) cout << endl;
		else if ((i + 1) % 3 == 0) cout << "\t";
	}
}
void ControladorHabitaciones::GenerarHabitaciones() {
	for (int i = 1; i <= 30; i++) {
		Habitacion* habitacion = new Habitacion(i);
		habitaciones->agregaFinal(habitacion);
	}
}
string ControladorHabitaciones::ObtenerEstadoHabitacionesString() {
	string estado = "";
	for (int i = 0; i < habitaciones->longitud(); i++) {
		// Si esta disponible agrega '1', si no, agrega '0'
		if (habitaciones->obtenerPos(i)->getDisponible()) {
			estado += "1";
		}
		else {
			estado += "0";
		}
	}
	return estado;
}
bool ControladorHabitaciones::verificarHabitacion(int numeroHabitacion) {
	for (int i = 0; i < habitaciones->longitud(); i++) {
		Habitacion* aux = habitaciones->obtenerPos(i);
		if (aux->getNumero() == numeroHabitacion) {
			if (aux->getDisponible())return true;
			else return false;
		}
	}
}
void ControladorHabitaciones::CargarEstadoHabitacionesString(string estado) {
	// Leemos el string y actualizamos los asientos que ya fueron generados
	for (int i = 0; i < estado.length() && i < habitaciones->longitud(); i++) {
		bool estaDisponible = (estado[i] == '1');
		habitaciones->obtenerPos(i)->setDisponible(estaDisponible);
	}
}
Lista<Habitacion*>* ControladorHabitaciones::getHabitaciones() {
	return habitaciones;
}
void ControladorHabitaciones::setHabitaciones(Lista<Habitacion*>* habitaciones) {
	this->habitaciones = habitaciones;
}
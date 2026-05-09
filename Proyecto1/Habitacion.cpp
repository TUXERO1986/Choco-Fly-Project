#include "Habitacion.h"
Habitacion::Habitacion(int numero) {
	this->numero = numero;
	this->disponible = true;
}
void Habitacion::MostrarHabitacion() {
	cout << numero;
}
int Habitacion::getNumero() { return numero; }
bool Habitacion::getDisponible() { return disponible; }
void Habitacion::setNumero(int numero) { this->numero = numero; }
void Habitacion::setDisponible(bool numero) { this->disponible = disponible; }

#include "Habitacion.h"
Habitacion::Habitacion(int numero, int tipo) {
	this->numero = numero;
	this->tipo = tipo;
	this->disponible = true;
}
void Habitacion::MostrarHabitacion() {
	cout << numero;
}
int Habitacion::getNumero() { return numero; }
int Habitacion::getTipo() { return tipo; }
bool Habitacion::getDisponible() { return disponible; }
void Habitacion::setNumero(int numero) { this->numero = numero; }
void Habitacion::setTipo(int tipo) { this->tipo= tipo; }
void Habitacion::setDisponible(bool numero) { this->disponible = disponible; }

#include "Hotel.h"
Hotel::Hotel(string nombre, string ciudad, float puntuacion, float precioNoche,ControladorHabitaciones* controladorHabitaciones) {
	this->nombre = nombre;
	this->ciudad = ciudad;
	this->puntuacion = puntuacion;
	this->precioNoche = precioNoche;
	this->controladorHabitaciones = controladorHabitaciones;
}
void Hotel::MostrarHotel() {
	cout << "Nombre: " << nombre << endl;
	cout << "Ciudad: " << ciudad << endl;
	cout << "Puntuacion: " << puntuacion << endl;
	cout << "Precio por noche: $" << precioNoche << endl;
}
void Hotel::MostrarHabitaciones() {
	controladorHabitaciones->MostrarHabitaciones();
}
string Hotel::getNombre() { return nombre; }
string Hotel::getCiudad() { return ciudad; }
float Hotel::getPuntuacion() { return puntuacion; }
float Hotel::getPrecioNoche() { return precioNoche; }
ControladorHabitaciones* Hotel::getControladorHabitaciones() { return controladorHabitaciones; }
void Hotel::setNombre(string nombre) { this->nombre = nombre; }
void Hotel::setCiudad(string ciudad) { this->ciudad = ciudad; }
void Hotel::setPuntuacion(float puntuacion) { this->puntuacion = puntuacion; }
void Hotel::setPrecioNoche(float precioNoche) { this->precioNoche = precioNoche; }

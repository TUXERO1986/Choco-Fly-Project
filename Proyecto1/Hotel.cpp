#include "Hotel.h"
Hotel::Hotel(string nombre, string ciudad, float puntuacion, float precioNoche,ControladorHabitaciones* controladorHabitaciones,int id) {
	this->nombre = nombre;
	this->ciudad = ciudad;
	this->puntuacion = puntuacion;
	this->precioNoche = precioNoche;
	this->id=id;
	this->controladorHabitaciones = controladorHabitaciones;
}
void Hotel::MostrarHotel() {
	cout << "Nombre: " << nombre << endl;
	cout << "Ciudad: " << ciudad << endl;
	cout << "Puntuacion: " << puntuacion << endl;
	cout << "Precio por noche: $" << precioNoche << endl;
	cout<< "ID: "<<to_string(id);
}
void Hotel::MostrarHabitaciones() {
	controladorHabitaciones->MostrarHabitaciones();
}
string Hotel::getNombre() { return nombre; }
string Hotel::getCiudad() { return ciudad; }
float Hotel::getPuntuacion() { return puntuacion; }
float Hotel::getPrecioNoche() { return precioNoche; }
int Hotel::getId(){ return id;}
ControladorHabitaciones* Hotel::getControladorHabitaciones() { return controladorHabitaciones; }
void Hotel::setNombre(string nombre) { this->nombre = nombre; }
void Hotel::setCiudad(string ciudad) { this->ciudad = ciudad; }
void Hotel::setPuntuacion(float puntuacion) { this->puntuacion = puntuacion; }
void Hotel::setPrecioNoche(float precioNoche) { this->precioNoche = precioNoche; }

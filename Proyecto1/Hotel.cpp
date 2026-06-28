#include "Hotel.h"
#include "Color.h"
#include "AsciiArt.h"
#include <iomanip>
#include <sstream>

using namespace ColorUI;

Hotel::Hotel(string nombre, string ciudad, float puntuacion, float precioNoche,ControladorHabitaciones* controladorHabitaciones, int id) {

	this->nombre = nombre;
	this->ciudad = ciudad;
	this->puntuacion = puntuacion;
	this->precioNoche = precioNoche;
	this->id=id;
	this->controladorHabitaciones = controladorHabitaciones;
}
void Hotel::MostrarHotel() {
	stringstream streamPrecio, streamPuntuacion;
	streamPrecio << fixed << setprecision(2) << precioNoche;
	streamPuntuacion << fixed << setprecision(1) << puntuacion;
    
	auto padRight = [](string str, int width) {
		if (str.length() < width) str.append(width - str.length(), ' ');
		return str;
	};

	string estrellas = "";
	int numEstrellas = (int)puntuacion;
	for(int i=0; i<numEstrellas; i++) estrellas += "*"; 

	string l1 = " HOTEL: " + nombre;
	string l1_full = padRight(l1, 60);

	string l2 = " CIUDAD: " + ciudad;
	string l2_right = "PRECIO/NOCHE: $" + streamPrecio.str() + " ";
	string l2_full = padRight(l2, 35) + padRight(l2_right, 25);

	string l3 = " PUNTUACION: " + streamPuntuacion.str() + "/5.0 " + estrellas;
	string l3_full = padRight(l3, 60);

	string tarjeta = 
		"+============================================================+\n"
		"|" + l1_full + "|\n"
		"+------------------------------------------------------------+\n"
		"|" + l2_full + "|\n"
		"|" + l3_full + "|\n"
		"+============================================================+";

	printSpriteAndCard(spriteHotel, Paletas::Tux, tarjeta, Paletas::dato);
}
void Hotel::MostrarHabitaciones() {
	controladorHabitaciones->MostrarHabitaciones();
}
string Hotel::getNombre() { return nombre; }
string Hotel::getCiudad() { return ciudad; }
float Hotel::getPuntuacion() { return puntuacion; }
float Hotel::getPrecioNoche() { return precioNoche+id*5; }
int Hotel::getId(){ return id;}
ControladorHabitaciones* Hotel::getControladorHabitaciones() { return controladorHabitaciones; }
void Hotel::setNombre(string nombre) { this->nombre = nombre; }
void Hotel::setCiudad(string ciudad) { this->ciudad = ciudad; }
void Hotel::setPuntuacion(float puntuacion) { this->puntuacion = puntuacion; }
void Hotel::setPrecioNoche(float precioNoche) { this->precioNoche = precioNoche; }

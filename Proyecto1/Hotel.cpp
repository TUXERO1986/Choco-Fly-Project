#include "Hotel.h"
#include "Color.h"
#include "AsciiArt.h"
#include <iomanip>
#include <sstream>

using namespace ColorUI;

Hotel::Hotel(string nombre, string ciudad, float puntuacion, float precioNoches, int id) : Servicio(id,"HOTEL",precioNoches){

	this-> habitaciones= new Lista<Habitacion*>();
	GenerarHabitaciones();
	this->nombre = nombre;
	this->ciudad = ciudad;
	this->puntuacion = puntuacion;
	this->precioNoche = precioNoches;
	this->id=id;
}
void Hotel::MostrarDatos() {
	stringstream streamPrecio, streamPuntuacion;
	streamPrecio << fixed << setprecision(2) << precioBase;
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
	for (int i = 0; i < habitaciones->longitud(); i++) {
		Habitacion* aux = habitaciones->obtenerPos(i);
		aux->MostrarHabitacion();
		cout << " ";
		if ((i + 1) % 6 == 0) cout << endl;
		else if ((i + 1) % 3 == 0) cout << "\t";
	}
}
void Hotel::GenerarHabitaciones() {
	for (int i = 1; i <= 30; i++) {
		Habitacion* habitacion = new Habitacion(i);
		habitaciones->agregaFinal(habitacion);
	}
}
string Hotel::ObtenerEstadoHabitacionesString() {
	string estado = "";
	for (int i = 0; i < habitaciones->longitud(); i++) {
	
		if (habitaciones->obtenerPos(i)->getDisponible()) {
			estado += "1";
		}
		else {
			estado += "0";
		}
	}
	return estado;
}
bool Hotel::verificarHabitacion(int numeroHabitacion) {
	for (int i = 0; i < habitaciones->longitud(); i++) {
		Habitacion* aux = habitaciones->obtenerPos(i);
		if (aux->getNumero() == numeroHabitacion) {
			if (aux->getDisponible()) return true;
			else return false;
		}
	}
	return false;
}
string Hotel::aTextoArchivo() {
    stringstream ss;
    ss << nombre << "," 
       << ciudad << "," 
       << puntuacion << "," 
       << precioBase << "," 
       << ObtenerEstadoHabitacionesString();
    
    return ss.str();
}
void Hotel::CargarEstadoHabitacionesString(string estado) {
	
	for (int i = 0; i < estado.length() && i < habitaciones->longitud(); i++) {
		bool estaDisponible = (estado[i] == '1');
		habitaciones->obtenerPos(i)->setDisponible(estaDisponible);
	}
}
Lista<Habitacion*>* Hotel::getHabitaciones() {
	return habitaciones;
}
void Hotel::setHabitaciones(Lista<Habitacion*>* habitaciones) {
	this->habitaciones = habitaciones;
}
string Hotel::getNombre() { return nombre; }
string Hotel::getCiudad() { return ciudad; }
float Hotel::getPuntuacion() { return puntuacion; }
int Hotel::getId(){ return id;}
void Hotel::setNombre(string nombre) { this->nombre = nombre; }
void Hotel::setCiudad(string ciudad) { this->ciudad = ciudad; }
void Hotel::setPuntuacion(float puntuacion) { this->puntuacion = puntuacion; }
void Hotel::setPrecioNoche(float precioNoche) { this->precioNoche = precioNoche; }

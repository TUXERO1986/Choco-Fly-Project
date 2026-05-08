#include "ReservaHotel.h"
ReservaHotel::ReservaHotel(string codigoUsuario, string nombreUsuario, string nombreHotel, string ciudad, float precioNoche, int noches)
	: Reserva(codigoUsuario, nombreUsuario) {
	this->nombreHotel = nombreHotel;
	this->ciudad = ciudad;
	this->precioNoche = precioNoche;
	this->noches = noches;
}
void ReservaHotel::MostrarReserva() {
	MostrarReserva();
	cout << "Hotel: " << nombreHotel << endl;
	cout << "Ciudad: " << ciudad << endl;
	cout << "Noches: " << noches << endl;
	cout << "Precio por Noche: " << precioNoche << endl;
}
string ReservaHotel::aTextoArchivo() {
	return codigoUsuario + "," + nombreUsuario + "," + nombreHotel + "," + ciudad + "," + to_string(precioNoche) + "," + to_string(noches);
}
string ReservaHotel::getNombreHotel() { return nombreHotel; }
string ReservaHotel::getCiudad() { return ciudad; }
int ReservaHotel::getNoches() { return noches; }

float ReservaHotel::getPrecioTotal() {
	return precioNoche * noches; 
}
void ReservaHotel::setNombreHotel(string nombreHotel) { this->nombreHotel = nombreHotel; }
void ReservaHotel::setCiudad(string ciudad) { this->ciudad = ciudad; }
void ReservaHotel::setNoches(int noches) { this->noches = noches; }
void ReservaHotel::setPrecioNoche(float precioNoche) { this->precioNoche = precioNoche	; }

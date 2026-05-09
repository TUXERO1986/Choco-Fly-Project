#include "ReservaHotel.h"
ReservaHotel::ReservaHotel(string codigoUsuario, string nombreUsuario, string nombreHotel, 
	string ciudad, float precioNoche, int noches,int habitacion,int tipoO,int tipoC,int tipoS)
	: Reserva(codigoUsuario, nombreUsuario) {
	this->nombreHotel = nombreHotel;
	this->ciudad = ciudad;
	this->precioNoche = precioNoche;
	this->noches = noches;
	this->tipoO = tipoO;
	this->tipoC = tipoC;
	this->tipoS = tipoS;
	this->habitacion = habitacion;
}
void ReservaHotel::MostrarReserva() {
	MostrarReserva();
	cout << "Hotel: " << nombreHotel << endl;
	cout << "Ciudad: " << ciudad << endl;
	cout << "Noches: " << noches << endl;
	cout << "Habitacion: " << habitacion << endl;
	cout << "Tipo de habitacion: " << tipoO << endl;
	cout << "Tipo de cama/s: " << tipoC << endl;
	cout << "Tipo de servicio: " << tipoS << endl;
	cout << "Precio Total " << getPrecioTotal() << endl;
}
string ReservaHotel::aTextoArchivo() {
	return codigoUsuario + "," + nombreUsuario + "," + nombreHotel + "," 
		+ ciudad + "," + to_string(precioNoche) + "," + to_string(noches)+ ","+
		to_string(habitacion) +","+to_string(tipoO)+"," + to_string(tipoC) +"," +
		to_string(tipoS);
}
string ReservaHotel::getNombreHotel() { return nombreHotel; }
string ReservaHotel::getCiudad() { return ciudad; }
int ReservaHotel::getNoches() { return noches; }
int ReservaHotel::getHabitacion() { return habitacion; }
int ReservaHotel::getTipoO() { return tipoO; }
int ReservaHotel::getTipoC() { return tipoC; }
int ReservaHotel::getTipoS() { return tipoS; }
float ReservaHotel::getPrecioTotal() {
	return precioNoche* noches+(tipoO+tipoC+tipoS)*30; 
}
void ReservaHotel::setNombreHotel(string nombreHotel) { this->nombreHotel = nombreHotel; }
void ReservaHotel::setCiudad(string ciudad) { this->ciudad = ciudad; }
void ReservaHotel::setNoches(int noches) { this->noches = noches; }
void ReservaHotel::setPrecioNoche(float precioNoche) { this->precioNoche = precioNoche	; }
void ReservaHotel::setHabitacion(int habitacion) { this->habitacion = habitacion; }
void ReservaHotel::setTipoO(int tipoO) { this->tipoO = tipoO; }
void ReservaHotel::setTipoC(int tipoC) { this->tipoC = tipoC; }
void ReservaHotel::setTipoS(int tipoS) { this->tipoS = tipoS; }
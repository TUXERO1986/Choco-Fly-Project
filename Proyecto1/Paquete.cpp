#include "Paquete.h"
Paquete::Paquete(Vuelo* vuelo, Hotel* hotel) {
	this->vueloIncluido = vuelo;
	this->hotelIncluido = hotel;
}
void Paquete::MostrarPaquete() {
	cout << "-----------------------------" << endl;
	cout << "Paquete Incluye:" << endl;
	if (vueloIncluido != nullptr) {
		vueloIncluido->MostrarVuelo();
	}
	else {
		cout << "No se incluyó vuelo." << endl;
	}
	if (hotelIncluido != nullptr) {
		hotelIncluido->MostrarHotel();
	}
	else {
		cout << "No se incluyó hotel." << endl;
	}
	cout << "-----------------------------" << endl;
}
Vuelo* Paquete::getVueloIncluido() { return vueloIncluido; }
Hotel* Paquete::getHotelIncluido() { return hotelIncluido; }
void Paquete::setVueloIncluido(Vuelo* vuelo) { this->vueloIncluido = vuelo; }
void Paquete::setHotelIncluido(Hotel* hotel) { this->hotelIncluido = hotel; }
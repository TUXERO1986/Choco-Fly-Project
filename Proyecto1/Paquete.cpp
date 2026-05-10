#include "Paquete.h"
Paquete::Paquete(Vuelo* vueloIda, Hotel* hotel) {
	this->vueloIncluido = vueloIda;
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
	cout << "Precio base: $" << getPrecioBase()<<endl;
	cout << "-----------------------------" << endl;
}
Hotel* Paquete::getHotelIncluido() { return hotelIncluido; }
Vuelo* Paquete::getVueloIncluido() { return vueloIncluido; }
void Paquete::setVueloIncluido(Vuelo* vuelo) { this->vueloIncluido	 = vuelo; }
void Paquete::setHotelIncluido(Hotel* hotel) { this->hotelIncluido = hotel; }
float Paquete::getPrecioBase() { return vueloIncluido->getPrecioBase() + hotelIncluido->getPrecioNoche(); }
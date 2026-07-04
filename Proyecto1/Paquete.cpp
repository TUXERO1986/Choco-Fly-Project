#include "Paquete.h"
#include "Color.h"
#include "AsciiArt.h"
#include <iomanip>
#include <sstream>

using namespace ColorUI;

Paquete::Paquete(Vuelo* vueloIda, Hotel* hotel,int id) : Servicio(id,"PAQUETE",vueloIda->getPrecioBase() + hotel->getPrecioBase()+id*5){
	this->vueloIncluido = vueloIda;
	this->hotelIncluido = hotel;
	this->id = id;
}
void Paquete::MostrarDatos() {
	stringstream streamPrecio;
	streamPrecio << fixed << setprecision(2) << precioBase;

	auto padRight = [](string str, int width) {
		if (str.length() < width) str.append(width - str.length(), ' ');
		return str;
	};

	string cabecera = 
		"+============================================================+\n"
		"| [*] PAQUETE PROMOCIONAL ESPECIAL                           |\n"
		"+============================================================+";
	
	printSpriteAndCard(spritePaquete, Paletas::Tux, cabecera, Paletas::Exito);

	if (vueloIncluido != nullptr) {
		vueloIncluido->MostrarDatos();
	}
	else {
		printGradient("  [!] No se incluyo vuelo.", Alerta, false, true);
	}
	
	if (hotelIncluido != nullptr) {
		hotelIncluido->MostrarDatos();
	}
	else {
		printGradient("  [!] No se incluyo hotel.", Alerta, false, true);
	}

	string l1_right = "TOTAL PAQUETE: $" + streamPrecio.str() + " ";
	string l1_full = padRight("", 30) + padRight(l1_right, 30);

	string pie = 
		"+============================================================+\n"
		"|" + l1_full + "|\n"
		"+============================================================+";

	printSpriteAndCard("", Paletas::Tux, pie, Paletas::Exito);
}
string Paquete::aTextoArchivo() {
    stringstream ss;
    ss << vueloIncluido->getOrigen() << "," 
       << vueloIncluido->getDestino() << "," 
       << vueloIncluido->getEscalas() << ","
       << vueloIncluido->getFecha() << "," 
       << vueloIncluido->getDistancia() << ","
       << hotelIncluido->getNombre() << "," 
       << hotelIncluido->getCiudad() << ","
       << hotelIncluido->getPuntuacion() << "," 
       << hotelIncluido->getPrecioBase();
       
    return ss.str();
}
Hotel* Paquete::getHotelIncluido() { return hotelIncluido; }
Vuelo* Paquete::getVueloIncluido() { return vueloIncluido; }
void Paquete::setVueloIncluido(Vuelo* vuelo) { this->vueloIncluido	 = vuelo; }
void Paquete::setHotelIncluido(Hotel* hotel) { this->hotelIncluido = hotel; }
int Paquete::getId() { return id; }
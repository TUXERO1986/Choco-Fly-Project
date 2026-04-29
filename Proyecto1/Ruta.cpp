#include "Ruta.h"
Ruta::Ruta() = default;
Ruta::Ruta(string origen,string destino,string aerolinea, float precio,float distancia) {
	this->origen = origen;
	this->destino = destino;
	this->aerolinea = aerolinea;
	this->precio = precio;
	this->distancia = distancia;
}
string Ruta::getOrigen() { return origen; }
string Ruta::getDestino() { return destino; }
string Ruta::getAerolinea() { return aerolinea; }
float Ruta::getPrecio() { return precio; }
float Ruta::getDistancia() { return distancia; }
void Ruta::setOrigen(string origen) { this->origen = origen; }
void Ruta::setDestino(string destino) { this->destino = destino; }
void Ruta::setAerolinea(string aerolinea) { this->aerolinea = aerolinea; }
void Ruta::setPrecio(float precio) { this->precio = precio; }
void Ruta::setDistancia(float distancia) { this->distancia = distancia; }
void Ruta::MostrarDatos() {
	cout << "Origen: " << origen << endl<<"Destino: " << destino<<endl<<"Aerolinea: "<<aerolinea<<endl<<
		"Precio: "<<precio<<endl<<"Distancia: "<<distancia<<endl;
}
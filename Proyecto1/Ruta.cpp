#include "Ruta.h"
Ruta::Ruta() = default;
Ruta::Ruta(string origen,string destino,float distancia) {
	this->origen = origen;
	this->destino = destino;
	this->distancia = distancia;
}
string Ruta::getOrigen() { return origen; }
string Ruta::getDestino() { return destino; }
float Ruta::getDistancia() { return distancia; }
void Ruta::setOrigen(string origen) { this->origen = origen; }
void Ruta::setDestino(string destino) { this->destino = destino; }
void Ruta::setDistancia(float distancia) { this->distancia = distancia; }
void Ruta::MostrarDatos() {
	cout << "Origen: " << origen << endl<<"Destino: " << destino<<endl<<"Distancia: "<<distancia<<endl;
}
#include "Vuelo.h"
Vuelo::Vuelo(string o, string d, string e, string f, float p) {
	this->origen = o;
	this->destino = d;
	this->escalas = e;
	this->fecha = f;
	this->precio = p;
}
void Vuelo::MostrarVuelo() {
	cout << "---------------------------------------" << endl;
	cout << "Origen: " << origen << endl;
	cout << "Destino: " << destino << endl;
	cout << "Escalas: " << escalas << endl;
	cout << "Fecha: " << fecha << endl;
	cout << "Precio: " << precio << endl;
	cout << "---------------------------------------" << endl;
}
string Vuelo::GetFechaPorDestinoYOrigen(string origen,string destino) {
	if (this->origen == origen && this->destino == destino) {
		return fecha;
	}
	return "";
}
string Vuelo::getFecha() { return fecha; }
float Vuelo::getPrecio() { return precio; }
string Vuelo::getOrigen() { return origen; }
string Vuelo::getDestino() { return destino; }
string Vuelo::getEscalas() { return escalas; }
void Vuelo::setOrigen(string o) { this->origen = o; }
void Vuelo::setDestino(string d) { this->destino = d; }
void Vuelo::setEscalas(string e) { this->escalas = e; }
void Vuelo::setFecha(string f) { this->fecha = f; }
void Vuelo::setPrecio(float p) { this->precio = p; }
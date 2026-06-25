#include "Vuelo.h"
#include "Color.h"
#include "AsciiArt.h"
#include <iomanip>
#include <sstream>

using namespace ColorUI;

Vuelo::Vuelo(string o, string d, string e, string f, float distancia, ControladorAsientos* controladorAsientos) {
	this->controladorAsientos = controladorAsientos;
	this->origen = o;
	this->destino = d;
	this->escalas = e;
	this->fecha = f;
	this->distancia = distancia;
}
void Vuelo::MostrarVuelo() {
	float precioBase = distancia * 0.7f;
	stringstream streamPrecio, streamDistancia;
	streamPrecio << fixed << setprecision(2) << precioBase;
	streamDistancia << fixed << setprecision(1) << distancia;
    
	auto padRight = [](string str, int width) {
		if (str.length() < width) str.append(width - str.length(), ' ');
		return str;
	};

	string l1 = " VUELO [" + origen + "] -> [" + destino + "]";
	string l1_right = "PRECIO: $" + streamPrecio.str() + " ";
	string l1_full = padRight(l1, 35) + padRight(l1_right, 23);

	string l2 = " FECHA: " + fecha;
	string l2_right = "ESCALAS: " + escalas + " ";
	string l2_full = padRight(l2, 35) + padRight(l2_right, 25);

	string l3 = " DISTANCIA: " + streamDistancia.str() + " km";
	string l3_full = padRight(l3, 60);

	string tarjeta = 
		"+============================================================+\n"
		"|" + l1_full + "|\n"
		"+------------------------------------------------------------+\n"
		"|" + l2_full + "|\n"
		"|" + l3_full + "|\n"
		"+============================================================+";

	printSpriteAndCard(spriteAvion, Paletas::Tux, tarjeta, Paletas::azul);
}
void Vuelo::MostrarAsientos() {
	controladorAsientos->MostrarAsientos();
}
string Vuelo::GetFechaPorDestinoYOrigen(string origen,string destino) {
	if (this->origen == origen && this->destino == destino) {
		return fecha;
	}
	return "";
}
string Vuelo::getFecha() { return fecha; }
string Vuelo::getOrigen() { return origen; }
string Vuelo::getDestino() { return destino; }
string Vuelo::getEscalas() { return escalas; }
float Vuelo::getDistancia() { return distancia; }
float Vuelo::getPrecioBase() { return distancia*0.7; }
ControladorAsientos* Vuelo::getControladorAsientos() {return controladorAsientos;}
void Vuelo::setOrigen(string o) { this->origen = o; }
void Vuelo::setDestino(string d) { this->destino = d; }
void Vuelo::setEscalas(string e) { this->escalas = e; }
void Vuelo::setFecha(string f) { this->fecha = f; }
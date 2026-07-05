#include "Vuelo.h"
#include "Color.h"
#include "AsciiArt.h"
#include <iomanip>
#include <sstream>

using namespace ColorUI;

Vuelo::Vuelo(string o, string d, string e, string f, float distancia, int id) : Servicio(id,"VUELO",distancia*0.7+id*5){
    this->asientos = new Lista<Asiento*>();
	GenerarAsientos();
	this->origen = o;
	this->destino = d;
	this->escalas = e;
	this->fecha = f;
	this->distancia = distancia;
	this->id=id;
}
void Vuelo::MostrarDatos() {
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
string Vuelo::GetFechaPorDestinoYOrigen(string origen,string destino) {
	if (this->origen == origen && this->destino == destino) {
		return fecha;
	}
	return "";
}
void Vuelo::MostrarAsientos() {
	for (int i = 0; i < asientos->longitud(); i++) {
		Asiento* aux = asientos->obtenerPos(i);
		aux->MostraAsiento();
		cout << " ";
		if ((i+1) % 6 == 0) cout << endl;
		else if ((i+1) % 3 == 0) cout << "\t";
	}
}
void Vuelo::GenerarAsientos() {
	for (int i = 1; i <= 30; i++) {
		Asiento* asiento = new Asiento(i);
		asientos->agregaFinal(asiento);
	}
}
string Vuelo::ObtenerEstadoAsientosString() {
	string estado = "";
	for (int i = 0; i < asientos->longitud(); i++) {
	
		if (asientos->obtenerPos(i)->getDisponible()) {
			estado += "1";
		}
		else {
			estado += "0";
		}
	}
	return estado;
}
bool Vuelo::VerificarAsiento(int numeroAsiento) {
	for (int i = 0; i < asientos->longitud(); i++) {
		Asiento* aux = asientos->obtenerPos(i);
		if (aux->getNumero() == numeroAsiento) {
			if (aux->getDisponible())return true;
			else return false;
		}
	}
	return false;
}
void Vuelo::CargarEstadoAsientosString(string estado) {
	
	for (int i = 0; i < estado.length() && i < asientos->longitud(); i++) {
		bool estaDisponible = (estado[i] == '1');
		asientos->obtenerPos(i)->setDisponible(estaDisponible);
	}
}
string Vuelo::aTextoArchivo() {
    stringstream ss;
    ss << origen << "," 
       << destino << "," 
       << escalas << "," 
       << fecha << "," 
       << distancia << "," 
       << ObtenerEstadoAsientosString();
       
    return ss.str();
}
Lista<Asiento*>* Vuelo::getAsientos() {
	return asientos;
}
void Vuelo::setAsientos(Lista<Asiento*>* asientos) {
	this->asientos = asientos;
}
string Vuelo::getFecha() { return fecha; }
string Vuelo::getOrigen() { return origen; }
string Vuelo::getDestino() { return destino; }
string Vuelo::getEscalas() { return escalas; }
float Vuelo::getDistancia() { return distancia; }
int Vuelo::getId(){return id;}
void Vuelo::setOrigen(string o) { this->origen = o; }
void Vuelo::setDestino(string d) { this->destino = d; }
void Vuelo::setEscalas(string e) { this->escalas = e; }
void Vuelo::setFecha(string f) { this->fecha = f; }
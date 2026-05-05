#include "Ticket.h"
Ticket::Ticket() = default;
Ticket::Ticket(string nombre,string origen, string destino, string escalas, float precio, float distancia, int equipaje, int equipajecabina){
	this->nombre = nombre;
	this->origen = origen;
	this->destino = destino;
	this->escalas = escalas;
	this->precio = precio;
	this->distancia = distancia	;
	this->equipaje = equipaje;
	this->equipajecabina = equipajecabina;
}
void Ticket::MostrarTicket() {
	cout << "-----------------------------" << endl;
	cout << "Origen: " << origen << endl;
	cout << "Destino: " << destino << endl;
	cout << "Escalas: " << escalas << endl;
	cout << "Precio: " << precio << endl;
	cout << "Distancia: " << distancia << endl;
	cout << "Equipaje: " << equipaje << endl;
	cout << "Equipaje de cabina: " << equipajecabina << endl;
	cout << "-----------------------------" << endl;
}
string Ticket::getNombre() { return nombre; }
string Ticket::getOrigen() { return origen; }
string Ticket::getDestino() { return destino; }
string Ticket::getEscalas() { return escalas; }
float Ticket::getPrecio() { return precio; }
float Ticket::getDistancia() { return distancia; }
int Ticket::getEquipaje() { return equipaje; }
int Ticket::getEquipajeCabina() { return equipajecabina; }
void Ticket::setEquipaje(int equipaje) { this->equipaje = equipaje; }
void Ticket::setEquipajeCabina(int equipajecabina) { this->equipajecabina = equipajecabina; }
void Ticket::setOrigen(string origen) { this->origen = origen; }
void Ticket::setDestino(string destino) { this->destino = destino; }
void Ticket::setEscalas(string escalas) { this->escalas = escalas; }
void Ticket::setPrecio(float precio) { this->precio = precio; }
void Ticket::setDistancia(float distancia) { this->distancia = distancia; }
void Ticket::setNombre(string nombre) { this->nombre = nombre; }
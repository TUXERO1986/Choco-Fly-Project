#include "Ticket.h"
Ticket::Ticket() = default;
Ticket::Ticket(string origen,string destino, string fecha,float precio,int equipaje,int equipajecabina,float distancia) {
	this->origen = origen;
	this->destino = destino;
	this->fecha = fecha;
	this->precio = precio;
	this->equipaje = equipaje;
	this->equipajecabina = equipajecabina;
	this->distancia = distancia;
}
void Ticket::MostrarTicket() {
	cout << "Origen: " << origen << endl;
	cout << "Destino: " << destino << endl;
	cout << "Precio: " << precio << endl;
	cout << "Equipaje: " << equipaje << endl;
	cout << "Equipaje de cabina: " << equipajecabina << endl;
	cout << "Distancia: " << distancia << endl;
	cout << "Fecha: " << fecha << endl;
}
string Ticket::getOrigen() { return origen; }
string Ticket::getDestino() { return destino; }
float Ticket::getPrecio() { return precio; }
int Ticket::getEquipaje() { return equipaje; }
int Ticket::getEquipajeCabina() { return equipajecabina; }
void Ticket::setOrigen(string origen) { this->origen = origen; }
void Ticket::setDestino(string destino) { this->destino = destino; }
void Ticket::setPrecio(float precio) { this->precio = precio; }
void Ticket::setEquipaje(int equipaje) { this->equipaje = equipaje; }
void Ticket::setEquipajeCabina(int equipajecabina) { this->equipajecabina = equipajecabina; }

#include "Ticket.h"
Ticket::Ticket(string codigoUsuario, string nombreUsuario, string origen, string destino, string escalas, float precio, float distancia, int equipaje, int equipajecabina)
    : Reserva(codigoUsuario, nombreUsuario)
{
	this->nombre = nombreUsuario;
	this->origen = origen;
	this->destino = destino;
	this->escalas = escalas;
	this->precio = precio;
	this->distancia = distancia	;
	this->equipaje = equipaje;
	this->equipajecabina = equipajecabina;
}
void Ticket::MostrarReserva() {
	cout << "Origen: " << origen << endl;
	cout << "Destino: " << destino << endl;
	cout << "Escalas: " << escalas << endl;
	cout << "Precio: " << precio << endl;
	cout << "Distancia: " << distancia << endl;
	cout << "Equipaje: " << equipaje << endl;
	cout << "Equipaje de cabina: " << equipajecabina << endl;
}
string Ticket::aTextoArchivo() {
	return "VUELO," + getCodigoUsuario() + "," + getNombre() + "," + origen + "," + destino + "," + escalas + "," + to_string(precio) + "," + to_string(distancia) + "," + to_string(equipaje) + "," + to_string(equipajecabina);
}
float Ticket::getPrecioTotal() {
	float costoEquipaje = equipaje * 10.0f; 
	float costoEquipajeCabina = equipajecabina * 20.0f; 
	return precio + costoEquipaje + costoEquipajeCabina;
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
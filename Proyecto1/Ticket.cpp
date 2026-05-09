#include "Ticket.h"
Ticket::Ticket(string codigoUsuario, string nombreUsuario, string origen, string destino, string escalas, float distancia, int equipaje, int equipajecabina,int clase,int asiento)
    : Reserva(codigoUsuario, nombreUsuario)
{
	this->nombre = nombreUsuario;
	this->origen = origen;
	this->destino = destino;
	this->escalas = escalas;
	this->distancia = distancia	;
	this->equipaje = equipaje;
	this->equipajecabina = equipajecabina;
	this->clase = clase;
	this->asiento = asiento;
}
void Ticket::MostrarReserva() {
	string clasestring;
	switch (clase) {
	case 1:clasestring = "ECONOMICA"; break;
	case 2:clasestring = "ECONOMICA PREMIUM"; break;
	case 3:clasestring = "EJECUTIVA"; break;
	case 4:clasestring = "PRIMERA CLASE"; break;
	}
	cout << "Origen: " << origen << endl;
	cout << "Destino: " << destino << endl;
	cout << "Escalas: " << escalas << endl;
	cout << "Distancia: " << distancia << endl;
	cout << "Equipaje: " << equipaje << endl;
	cout << "Equipaje de cabina: " << equipajecabina << endl;
	cout << "Asiento: " << asiento << endl;
	cout << "Clase: " << clasestring;
	cout << "Precio Total: " << getPrecioTotal() << endl;
}
string Ticket::aTextoArchivo() {
	return "VUELO," + getCodigoUsuario() + "," + getNombre() + "," + origen + "," + destino + "," + escalas + "," + to_string(getPrecioTotal()) 
		+ "," + to_string(distancia) + "," + to_string(equipaje) + "," + to_string(equipajecabina)+","+to_string(clase)+","+to_string(asiento);
}
float Ticket::getPrecioTotal() {
	float costoEquipaje = (equipaje-1) * 10.0f; 
	float costoEquipajeCabina = equipajecabina * 20.0f; 
	return (distancia*0.8)*clase + costoEquipaje*10 + costoEquipajeCabina*40;
}
string Ticket::getNombre() { return nombre; }
string Ticket::getOrigen() { return origen; }
string Ticket::getDestino() { return destino; }
string Ticket::getEscalas() { return escalas; }
float Ticket::getDistancia() { return distancia; }
int Ticket::getEquipaje() { return equipaje; }
int Ticket::getEquipajeCabina() { return equipajecabina; }
void Ticket::setEquipaje(int equipaje) { this->equipaje = equipaje; }
void Ticket::setEquipajeCabina(int equipajecabina) { this->equipajecabina = equipajecabina; }
void Ticket::setOrigen(string origen) { this->origen = origen; }
void Ticket::setDestino(string destino) { this->destino = destino; }
void Ticket::setEscalas(string escalas) { this->escalas = escalas; }
void Ticket::setDistancia(float distancia) { this->distancia = distancia; }
void Ticket::setNombre(string nombre) { this->nombre = nombre; }
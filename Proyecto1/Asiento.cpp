#include "Asiento.h"
Asiento::Asiento(int numero,int clase) {
	this->numero = numero;
	this->clase = clase;
	this->disponible = true;
}
void Asiento::MostraAsiento() {
	cout << numero;
}
bool Asiento::getDisponible() {
	return disponible;
}
int Asiento::getClase() {
	return clase;
}
int Asiento::getNumero() {
	return numero;
}
void Asiento::setDisponible(bool disponible) {
	this->disponible = disponible;
}
void Asiento::setNumero(int numero) {
	this->numero = numero;
}
void Asiento::setClase(int clase) { 
	this->clase = clase; 
}
#include "Asiento.h"
Asiento::Asiento(int numero) {
	this->numero = numero;
	this->disponible = true;
}
void Asiento::MostraAsiento() {
	cout << numero;
}
bool Asiento::getDisponible() {
	return disponible;
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

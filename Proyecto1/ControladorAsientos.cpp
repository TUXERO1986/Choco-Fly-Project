#include "ControladorAsientos.h"
ControladorAsientos::ControladorAsientos() {
	this->asientos = new Lista<Asiento*>();
}
void ControladorAsientos::MostrarAsientos() {
	for (int i = 1; i <= asientos->longitud(); i++) {
		Asiento* aux = asientos->obtenerPos(i);
		aux->MostraAsiento();
		cout << " ";
		if (i % 6 == 0) cout << endl;
		else if (i % 3 == 0) cout << "\t";
	}
}
void ControladorAsientos::GenerarAsientos() {
	for (int i = 1; i <= 30; i++) {
		Asiento* asiento = new Asiento(i);
		asientos->agregaFinal(asiento);
	}
}
Lista<Asiento*>* ControladorAsientos::getAsientos() {
	return asientos;
}
void ControladorAsientos::setAsientos(Lista<Asiento*>* asientos) {
	this->asientos = asientos;
}
#include "ControladorAsientos.h"
ControladorAsientos::ControladorAsientos() {
	this->asientos = new Lista<Asiento*>();
	GenerarAsientos();
}
void ControladorAsientos::MostrarAsientos() {
	for (int i = 0; i < asientos->longitud(); i++) {
		Asiento* aux = asientos->obtenerPos(i);
		aux->MostraAsiento();
		cout << " ";
		if ((i+1) % 6 == 0) cout << endl;
		else if ((i+1) % 3 == 0) cout << "\t";
	}
}
void ControladorAsientos::GenerarAsientos() {
	for (int i = 1; i <= 30; i++) {
		Asiento* asiento = new Asiento(i);
		asientos->agregaFinal(asiento);
	}
}
string ControladorAsientos::ObtenerEstadoAsientosString() {
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
bool ControladorAsientos::VerificarAsiento(int numeroAsiento) {
	for (int i = 0; i < asientos->longitud(); i++) {
		Asiento* aux = asientos->obtenerPos(i);
		if (aux->getNumero() == numeroAsiento) {
			if (aux->getDisponible())return true;
			else return false;
		}
	}
	return false;
}
void ControladorAsientos::CargarEstadoAsientosString(string estado) {
	
	for (int i = 0; i < estado.length() && i < asientos->longitud(); i++) {
		bool estaDisponible = (estado[i] == '1');
		asientos->obtenerPos(i)->setDisponible(estaDisponible);
	}
}
Lista<Asiento*>* ControladorAsientos::getAsientos() {
	return asientos;
}
void ControladorAsientos::setAsientos(Lista<Asiento*>* asientos) {
	this->asientos = asientos;
}
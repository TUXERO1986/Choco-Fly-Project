#include "ControladorPaquetes.h"
ControladorPaquetes::ControladorPaquetes() {
	paquetes = new Lista<Paquete*>();
	controladorArchivos = new ControladorArchivos("Paquetes.txt");
	controladorArchivos->LeerArchivoPaquetes(paquetes);
}
ControladorPaquetes::~ControladorPaquetes() {
	for (int i = 0; i < paquetes->longitud(); i++) {
		delete paquetes->obtenerPos(i);
	}
	delete paquetes;
}
void ControladorPaquetes::MostrarPaquetesCiudades(string ciudadOrigen, string ciudadDestino) {
	for (int i = 0; i < paquetes->longitud(); i++) {
		Paquete* aux = paquetes->obtenerPos(i);
		if (aux->getVueloIncluido()->getOrigen() == ciudadOrigen && aux->getVueloIncluido()->getDestino() == ciudadDestino) {
			cout << "Pauquete #" << i << ":" << endl;
			aux->MostrarPaquete();
			cout << endl;
		}
	}
}
void ControladorPaquetes::GenerarPaquetes(int contador, Lista<Hotel*>* listhoteles, Lista<Vuelo*>* listvuelos) {
	controladorArchivos->VaciarArchivo();
	for (int i = 0; i < contador; i++) {
		int indiceHotel = rand() % listhoteles->longitud();
		int indiceVuelo = rand() % listvuelos->longitud();
		Hotel* hotelSeleccionado = listhoteles->obtenerPos(indiceHotel);
		Vuelo* vueloSeleccionado = listvuelos->obtenerPos(indiceVuelo);
		if (hotelSeleccionado->getCiudad() != vueloSeleccionado->getDestino())continue;
		AgregarNuevoPaquete(listvuelos->obtenerPos(indiceVuelo), listhoteles->obtenerPos(indiceHotel));
	}
}
void ControladorPaquetes::AgregarNuevoPaquete(Vuelo* vueloIda, Hotel* hotel) {
	Paquete* nuevoPaquete = new Paquete(vueloIda, hotel);
	paquetes->agregaFinal(nuevoPaquete);
	controladorArchivos->GuardarDatoArchivoPaquetes(nuevoPaquete);
}
void ControladorPaquetes::MostrarPaquetes() {
	for (int i = 0; i < paquetes->longitud(); i++) {
		Paquete* aux = paquetes->obtenerPos(i);
		aux->MostrarPaquete();
	}
}
Lista<Paquete*>* ControladorPaquetes::getPaquetes() { return paquetes; }
void ControladorPaquetes::setPaquetes(Lista<Paquete*>* paquetes) { this->paquetes = paquetes; }

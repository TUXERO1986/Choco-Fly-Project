#include "ControladorPrincipal.h"
ControladorPrincipal::ControladorPrincipal() {
	controladorRutas = new ControladorRutas();
	controladorHoteles = new ControladorHoteles();
	controladorTickets = new ControladorTickets();
	controladorVuelos = new ControladorVuelos();
	controladorPaquetes = new ControladorPaquetes();
}
ControladorPrincipal::~ControladorPrincipal() {
	delete controladorRutas;
	delete controladorHoteles;
	delete controladorTickets;
	delete controladorPaquetes;
}
void ControladorPrincipal::GenerarDatos(int cantidadVuelos, int cantidadHoteles, int cantidadPaquetes) {
	GenerarVuelos(cantidadVuelos);
	GenerarHoteles(cantidadHoteles);
	GenerarPaquetes(cantidadPaquetes);
}
void ControladorPrincipal::GenerarVuelos(int cantidadVuelos) {
	controladorVuelos->GenerarVuelos(cantidadVuelos, controladorRutas->getRutas());
}
void ControladorPrincipal::GenerarHoteles(int cantidadHoteles) {
	controladorHoteles->GenerarHoteles(cantidadHoteles, controladorRutas->getMapaCiudades());
}
void ControladorPrincipal::GenerarPaquetes(int cantidadPaquetes) {
	controladorPaquetes->GenerarPaquetes(cantidadPaquetes, controladorHoteles->getHoteles(), controladorVuelos->getVuelos());
}
void ControladorPrincipal::EliminarVuelo(int indiceVuelo) {
	controladorVuelos->getVuelos()->eliminaPos(indiceVuelo);
}
void ControladorPrincipal::EliminarHotel(int indiceHotel) {
	controladorHoteles->getHoteles()->eliminaPos(indiceHotel);
}
void ControladorPrincipal::EliminarPaquete(int indicePaquete) {
	controladorPaquetes->getPaquetes()->eliminaPos(indicePaquete);
}
void ControladorPrincipal::EliminarTicket(int indiceTicket) {
	controladorTickets->getTickets()->eliminaPos(indiceTicket);
}
void ControladorPrincipal::ConsultarVuelos(string origen, string destino) {
	Lista<Ruta*>* rutasEncontradas = controladorRutas->BuscarRutaMasCorta(origen, destino);
	controladorVuelos->GenerarVuelosConEscala(origen, destino, rutasEncontradas);
}
void ControladorPrincipal::ComprarTicket(int indiceVuelo, string nombre,int equipaje, int equipajecabina) {
	Vuelo* vueloSeleccionado = controladorVuelos->ObtenerVueloPorPosicion(indiceVuelo);
	if (vueloSeleccionado != nullptr) {
		controladorTickets->AgregarNuevoTicket(nombre, vueloSeleccionado->getOrigen(), 
			vueloSeleccionado->getDestino(), vueloSeleccionado->getEscalas(), 
			vueloSeleccionado->getPrecio(), vueloSeleccionado->getDistancia(), equipaje, equipajecabina);
	}
}
void ControladorPrincipal::MostrarVuelos() {
	controladorVuelos->MostrarVuelos();
}
void ControladorPrincipal::MostrarHoteles() {
	controladorHoteles->MostrarHoteles();
}
void ControladorPrincipal::MostrarPaquetes() {
	controladorPaquetes->MostrarPaquetes();
}
void ControladorPrincipal::MostrarTickets() {
	controladorTickets->MostrarTickets();
}
ControladorHoteles* ControladorPrincipal::getControladorHoteles() { return controladorHoteles; }
ControladorPaquetes* ControladorPrincipal::getControladorPaquetes() { return controladorPaquetes; }
ControladorTickets* ControladorPrincipal::getControladorTickets() { return controladorTickets; }
ControladorVuelos* ControladorPrincipal::getControladorVuelos() { return controladorVuelos; }
ControladorRutas* ControladorPrincipal::getControladorRutas() { return controladorRutas; }

#include "ControladorTickets.h"
ControladorTickets::ControladorTickets() {
	controladorArchivos = new ControladorArchivos("Tickets.txt");
	tickets = new Lista<Ticket*>();
	controladorArchivos->LeerArchivoTickets(tickets);
}
ControladorTickets::~ControladorTickets() {
	for (int i = 0; i < tickets->longitud(); i++) {
		delete tickets->obtenerPos(i);
	}
	delete tickets;
}
void ControladorTickets::AgregarNuevoTicket(string nombre,string origen, string destino, string escalas, float precio, float distancia, int equipaje, int equipajecabina) {
	Ticket* nuevoTicket = new Ticket(nombre,origen, destino, escalas, precio, distancia, equipaje, equipajecabina);
	tickets->agregaFinal(nuevoTicket);
	controladorArchivos->GuardarDatoArchivoTickets(nuevoTicket);
}
void ControladorTickets::MostrarTickets() {
	for (int i = 0; i < tickets->longitud(); i++) {
		Ticket* aux = tickets->obtenerPos(i);
		aux->MostrarTicket();
	}
}
Lista<Ticket*>* ControladorTickets::getTickets() { return tickets; }
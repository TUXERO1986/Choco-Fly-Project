#pragma once
#include "ControladorArchivos.h"
class ControladorTickets
{
private:
	Lista<Ticket*>* tickets;
	ControladorArchivos* controladorArchivos;
public:
	ControladorTickets();
	~ControladorTickets();
	void AgregarNuevoTicket(string nombre,string origen, string destino, string escalas, float precio, float distancia, int equipaje, int equipajecabina);
	void MostrarTickets();
	Lista<Ticket*>* getTickets();
};


#pragma once
#include "ControladorPaquetes.h"
#include "ControladorHoteles.h"
#include "ControladorTickets.h"
#include "ControladorVuelos.h"
#include "ControladorRutas.h"
class ControladorPrincipal
{
private:
	ControladorVuelos* controladorVuelos;
	ControladorHoteles* controladorHoteles;
	ControladorPaquetes* controladorPaquetes;
	ControladorTickets* controladorTickets;
	ControladorRutas* controladorRutas;
public:
	ControladorPrincipal();
	~ControladorPrincipal();
	void GenerarDatos(int cantidadVuelos, int cantidadHoteles, int cantidadPaquetes);
	void GenerarVuelos(int cantidadVuelos);
	void GenerarHoteles(int cantidadHoteles);
	void GenerarPaquetes(int cantidadPaquetes);
	void EliminarVuelo(int indiceVuelo);
	void EliminarHotel(int indiceHotel);
	void EliminarPaquete(int indicePaquete);
	void EliminarTicket(int indiceTicket);
	void ConsultarVuelos(string origen, string destino);
	void MostrarVuelos();
	void MostrarHoteles();
	void MostrarPaquetes();
	void MostrarTickets();
	void ComprarTicket(int indiceVuelo, string nombre,int equipaje, int equipajecabina);
	ControladorHoteles* getControladorHoteles();
	ControladorPaquetes* getControladorPaquetes();
	ControladorTickets* getControladorTickets();
	ControladorVuelos* getControladorVuelos();
	ControladorRutas* getControladorRutas();
};


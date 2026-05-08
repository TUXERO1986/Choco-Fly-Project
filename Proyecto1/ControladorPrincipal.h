#pragma once
#include "ControladorPaquetes.h"
#include "ControladorHoteles.h"
#include "ControladorReservas.h"
#include "ControladorVuelos.h"
#include "ControladorRutas.h"
#include "ControladorUsuarios.h"
class ControladorPrincipal
{
private:
	ControladorVuelos* controladorVuelos;
	ControladorHoteles* controladorHoteles;
	ControladorPaquetes* controladorPaquetes;
	ControladorReservas* controladorReservas;
	ControladorRutas* controladorRutas;
	ControladorUsuarios* controladorUsuarios;

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
	void EliminarReserva(int indiceReserva);
	void ConsultarVuelos(string origen, string destino);
	void MostrarVuelos();
	void MostrarHoteles();
	void MostrarPaquetes();
	void MostrarReservasAdmin();
	void MostrarReservasUsuario(Usuario* userActual);
	void MostrarVuelosFltrados(string origen, string destino,string fecha1,string fecha2);
	void MostrarUsuariosAdmin();
	void ReservarHotel(int indiceHotel, string codigoUsuario, string nombreUsuario, int noches);
	void ReservarPaquete(int indicePaquete, Usuario* userActual);
	void ComprarTicket(int indiceVuelo, Usuario* usuariActual);
	Usuario* VerificarInicioSesion(string nombre, string correo, string password);
	ControladorHoteles* getControladorHoteles();
	ControladorPaquetes* getControladorPaquetes();
	ControladorReservas* getControladorReservas	();
	ControladorVuelos* getControladorVuelos();
	ControladorRutas* getControladorRutas();
};


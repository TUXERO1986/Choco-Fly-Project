#pragma once
#include "ControladorPaquetes.h"
#include "ControladorHoteles.h"
#include "ControladorReservas.h"
#include "ControladorVuelos.h"
#include "ControladorRutas.h"
#include "ControladorUsuarios.h"

#include "GestionPantallas.h"

#include <conio.h>
using namespace ColorUI;
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
	void AgregarVuelo(string origen, string destino, string escalas, string fecha, float distancia);
	void AgregarHotel(string nombre, string ciudad, float puntuacion, float precioNoche);
	void AgregarPaquete(Vuelo* vueloIda, Hotel* hotel);
	void AgregarReserva(Reserva* nuevaReserva);
	void AgregarUsuario(string nombre, string correo, string password);
	void AgregarRuta(string origen, string destino, float distancia);
	void EliminarRuta(int indiceRuta);
	void EliminarVuelo(int indiceVuelo);
	void EliminarHotel(int indiceHotel);
	void EliminarPaquete(int indicePaquete);
	void EliminarReserva(int indiceReserva);
	void EliminarUsuario(int indiceUsuario);
	void MostrarRutas();
	void MostrarVuelos();
	void MostrarHoteles();
	void MostrarPaquetes();
	void MostrarReservas();
	void MostrarUsuarios();
	void FilrarVuelosPorOrigenDestino(string origen, string destino);
	void FiltrarUsuariosPorNombre(string nombreBusqueda);
	void FiltrarRutasPorOrigen(string ciudadBusqueda);
	void FiltrarRutasPorDestino(string ciudadBusqueda);
	void FiltrarHotelesPorCiudad(string ciudadBusqueda);
	void FiltrarPaquetesPorDestino(string ciudadBusqueda);
	void FiltrarPaquetesPorOrigen(string ciudadBusqueda);
	void FiltrarVuelosPorFecha(string fechaBusqueda);
	void FitrarVuelosPorOrigen(string origenBusqueda);
	void FiltrarVuelosPorDestino(string destinoBusqueda);
	void FiltrarReservasPorTipo(string tipoBusqueda);
	void FiltrarReservasPorTipoUsuario(string tipoBusqueda, string codigousuario);
	void FiltrarReservasPorUsuario(string codigoUsuario);
	void FiltrarVuelosPorPresupuesto(float presupuestoMaximo);
	void FiltrarHotelesPorPresupuesto(float presupuestoMaximo);
	void FiltrarPaquetesPorPresupuesto(float presupuestoMaximo);
	void FiltrarHotelesPorMayorCalificacion();
	void FiltrarVuelosDeMayorAMenorPrecio();
	void FiltrarHotelesDeMayorAMenorPrecio();
	void FiltrarPaquetesDeMayorAMenorPrecio();
	void FiltrarUsuarioPorCodigo(string codigo);
	bool CancelarReservaUsuario(string codigoUsuario, int indiceReservaLocal);
	void CalificarHotel(string nombreHotel, float nuevaPuntuacion);
	void ObtenerIngresosTotales();
	bool ConsultarVuelos(string origen, string destino);
	bool VerificarHoteles(string ciudad);
	bool VerificarPaquetes(string destino);
	bool VerificarReservas(string codigo);
	void MostrarReservasUsuario(Usuario* userActual);
	void ReservarHotel(int indiceHotel, Usuario* userActual,string fecha, int noches,int habtiacion,int tipoO,int tipoC,int tipoS);
	void ReservarPaquete(int indicePaquete, Usuario* userActual, int noches,
		int maletasBodegaIda, int maletasBodegaRetorno, int clase, int asiento);
	bool VerificarAsiento(int numeroAsiento,int indiceVuelo);
	bool VerificarHabitacion(int numeroHabitacion,int indiceHotel);
	void MostrarAsientos(int indiiceVuelo);
	void MostrarHabitaciones(int indiiceHabitacion);
	void ComprarTicket(int indiceVuelo, Usuario* usuariActual,int equipajeBoveda,int equipajeCabina,int asiento,int clase);
	Usuario* VerificarInicioSesion(string nombre, string correo, string password);
	ControladorHoteles* getControladorHoteles();
	ControladorPaquetes* getControladorPaquetes();
	ControladorReservas* getControladorReservas	();
	ControladorVuelos* getControladorVuelos();
	ControladorRutas* getControladorRutas();
	ControladorUsuarios* getControladorUsuarios();

	void GuardarDatosEnArchivos();

};


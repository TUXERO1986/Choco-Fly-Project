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
	void FiltrarHotelesPorCiudad(string ciudadBusqueda);//ryanmaricon
	void FiltrarPaquetesPorDestino(string ciudadBusqueda);
	void FiltrarPaquetesPorOrigen(string ciudadBusqueda);//noesta
	void FiltrarVuelosPorFecha(string fechaBusqueda);//noesta
	void FitrarVuelosPorOrigen(string origenBusqueda);//noesta
	void FiltrarVuelosPorDestino(string destinoBusqueda);//noesta
	void FiltrarReservasPorTipo(string tipoBusqueda);
	void FiltrarReservasPorTipoUsuario(string tipoBusqueda, string codigousuario);
	void FiltrarReservasPorUsuario(string codigoUsuario);
	void FiltrarVuelosPorPresupuesto(float presupuestoMaximo);//noesta
	void FiltrarHotelesPorPresupuesto(float presupuestoMaximo);//noesta
	void FiltrarPaquetesPorPresupuesto(float presupuestoMaximo);//noesta
	void FiltrarHotelesPorMayorCalificacion();
	void FiltrarVuelosDeMayorAMenorPrecio();
	void FiltrarHotelesDeMayorAMenorPrecio();
	void FiltrarPaquetesDeMayorAMenorPrecio();
	void FiltrarUsuarioPorCodigo(string codigo);
	bool CancelarReservaUsuario(string codigoUsuario, int indiceReservaLocal);//noesta
	void CalificarHotel(string nombreHotel, float nuevaPuntuacion);//noesta
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
	// agregue esta funcion para el ui para que se pueda guardar la persistencia cada vez que se compra un t
	// icket o se reserva una habitacion, asi no se pierde la informacion aunque el programa se cierre
	//Guardar datos
	void GuardarDatosEnArchivos();

};


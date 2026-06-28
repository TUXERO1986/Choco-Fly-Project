#pragma once
#include "Lista.h"
#include "Ruta.h"
#include "CiudadID.h"
#include "Vuelo.h"
#include "Paquete.h"
#include "Hotel.h"
#include "ReservaVuelo.h"
#include "Registro.h"
#include "ReservaHotel.h"
#include "ReservaPaquete.h"
#include "Usuario.h"
#include <sstream>
#include <fstream>
#include <string>
#include <functional>
class ControladorArchivos
{ 
private:
	string nombrearchivo;
	function<size_t(Lista<CiudadID*>* , string)> ObtenerIdCiudad;
public:
	ControladorArchivos();
	ControladorArchivos(string);

	void LeerArchivoRutas(Lista<Lista<int>*>*,Lista<Ruta*>*, Lista<CiudadID*>*);
	void GardarDatoArchivoRutas(Ruta*);
	void LeerArchivoVuelos(Lista<Vuelo*>*);
	void GuardarDatoArchivoVuelos(Vuelo*);
	void GuardarDatoArchivoPaquetes(Paquete*);
	void LeerArchivoPaquetes(Lista<Paquete*>*);
	void GuardarDatoArchivoHoteles(Hotel*);
	void LeerArchivoHoteles(Lista<Hotel*>*);
	void LeerArchivoRegistros(Lista<Registro*>* registros);
    void GuardarDatoArchivoRegistros(Registro* r);
	void LeerArchivoUsuarios(Lista<Usuario*>* usuarios);
	void GuardarDatoArchivoUsuarios(Usuario* usuario);
	void LeerArchivoReservas(Lista<Reserva*>* listaDestino);
	void GuardarDatoArchivoReservas(Reserva* reserva);
	void VaciarArchivo();
};


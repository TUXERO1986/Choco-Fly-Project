#pragma once
#include "Lista.h"
#include "ArbolAVLMiltiClave.h"
#include "ArbolAVL.h"
#include "ArbolAVLClave.h"
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

	void LeerArchivoRutas(Lista<Lista<int>*>* conexiones, Lista<Ruta*>* rutas, Lista<CiudadID*>* MapaCiudades, ArbolAVLClave<CiudadID*, string>* indiceCiudadesPorNombre);
	void GardarDatoArchivoRutas(Ruta*);
	void LeerArchivoVuelos(Lista<Vuelo*>*,ArbolAVLMultiClave<Vuelo*, string>*,ArbolAVL<Vuelo*>*);
	void GuardarDatoArchivoVuelos(Vuelo*);
	void GuardarDatoArchivoPaquetes(Paquete*);
	void LeerArchivoPaquetes(Lista<Paquete*>*,ArbolAVLMultiClave<Paquete*, string>* ,ArbolAVL<Paquete*>*);
	void GuardarDatoArchivoHoteles(Hotel*);
	void LeerArchivoHoteles(Lista<Hotel*>*,ArbolAVLMultiClave<Hotel*, string>*,ArbolAVL<Hotel*>*);
	void LeerArchivoRegistros(Lista<Registro*>* registros);
    void GuardarDatoArchivoRegistros(Registro* r);
	void LeerArchivoUsuarios(Lista<Usuario*>* usuarios);
	void GuardarDatoArchivoUsuarios(Usuario* usuario);
	void LeerArchivoReservas(Lista<Reserva*>* listaDestino, ArbolAVLClave<Reserva*, int>* indiceReservasPorID);
	void GuardarDatoArchivoReservas(Reserva* reserva);
	void VaciarArchivo();
};


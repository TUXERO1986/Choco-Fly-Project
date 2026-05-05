#pragma once
#include "Lista.h"
#include "Ruta.h"
#include "CiudadID.h"
#include "Vuelo.h"
#include "Paquete.h"
#include "Hotel.h"
#include "Ticket.h"
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

	void LeerArchivo(Lista<Lista<int>*>*,Lista<Ruta*>*, Lista<CiudadID*>*);
	void LeerArchivoVuelos(Lista<Vuelo*>*);
	void GuardarDatoArchivoVuelos(Vuelo*);
	void GuardarDatoArchivoPaquetes(Paquete*);
	void LeerArchivoPaquetes(Lista<Paquete*>*);
	void GuardarDatoArchivoHoteles(Hotel*);
	void LeerArchivoHoteles(Lista<Hotel*>*);
	void GuardarDatoArchivoTickets(Ticket*);
	void LeerArchivoTickets(Lista<Ticket*>*);
	void VaciarArchivo();
};


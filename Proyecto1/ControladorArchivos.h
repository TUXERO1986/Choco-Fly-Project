#pragma once
#include "Lista.h"
#include "Ruta.h"
#include "CiudadID.h"
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
	//void LeerArchivo(std::string);
	//void GuardarDatoArchivo(std::string);
};


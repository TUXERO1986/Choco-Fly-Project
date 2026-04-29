#pragma once
#include "Lista.h"
#include "Ruta.h"
#include "CiudadId.h"
#include <sstream>
#include <fstream>
#include <string>
class ControladorArchivos
{ 
private:
	string nombrearchivo;
public:
	ControladorArchivos();
	ControladorArchivos(string);

	void LeerArchivo(Lista<Lista<int>*>*,Lista<Ruta*>*, Lista<CiudadId*>*);
	//void LeerArchivo(std::string);
	//void GuardarDatoArchivo(std::string);
};


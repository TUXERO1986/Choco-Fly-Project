#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "Lista.h"
#include "Ruta.h"
#include "CiudadesId.h"
using namespace std;
class ControladorArchivos
{ 
private:
	std::string nombrearchivo;
public:
	ControladorArchivos();
	ControladorArchivos(std::string);

	void LeerArchivo(Lista<Lista<int>*>*,Lista<Ruta*>*, Lista<CiudadesId*>*);
	void LeerArchivo(std::string);
	void GuardarDatoArchivo(std::string);
};


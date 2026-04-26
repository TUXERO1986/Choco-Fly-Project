
#include <string>
#include "CiudadId.h"

CiudadesId::CiudadesId(){}
CiudadesId::CiudadesId(std::string nombre, int id) {
	this->nombre = nombre;
	this->id = id;
}
std::string CiudadesId::getNombre() {
	return nombre;
}
int CiudadesId::getId() {
	return id;
}
void CiudadesId::setId(int id) {
	this->id = id; 
}
void CiudadesId::setNombre(std::string nombre) { 
	this->nombre = nombre; 
}
int CiudadesId::getIdPorNombre(std::string nombre) {
	if (this->nombre == nombre)return id;
}
std::string CiudadesId::getNombrePorId(int id) {
	if (this->id == id)return nombre;
}

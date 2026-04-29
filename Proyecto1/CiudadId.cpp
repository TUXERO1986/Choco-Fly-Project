#include "CiudadId.h"
CiudadId::CiudadId() = default;
CiudadId::CiudadId(std::string nombre, int id) {
	this->nombre = nombre;
	this->id = id;
}
std::string CiudadId::getNombre() {
	return nombre;
}
int CiudadId::getId() {
	return id;
}
void CiudadId::setId(int id) {
	this->id = id; 
}
void CiudadId::setNombre(std::string nombre) { 
	this->nombre = nombre; 
}
int CiudadId::getIdPorNombre(std::string nombre) {
	if (this->nombre == nombre)return id;
}
std::string CiudadId::getNombrePorId(int id) {
	if (this->id == id)return nombre;
}
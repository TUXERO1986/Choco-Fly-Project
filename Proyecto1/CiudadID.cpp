#include "CiudadID.h"
CiudadID::CiudadID() = default;
CiudadID::CiudadID(std::string nombre, int id) {
	this->nombre = nombre;
	this->id = id;
}
std::string CiudadID::getNombre() {
	return nombre;
}
int CiudadID::getId() {
	return id;
}
void CiudadID::setId(int id) {
	this->id = id;
}
void CiudadID::setNombre(std::string nombre) {
	this->nombre = nombre;
}
int CiudadID::getIdPorNombre(std::string nombre) {
	if (this->nombre == nombre) return id;
	return -1;
}
std::string CiudadID::getNombrePorId(int id) {
	if (this->id == id) return nombre;
	return "";
}
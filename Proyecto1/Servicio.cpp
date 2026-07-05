#include "Servicio.h"
Servicio::Servicio(int id, string tipoServicio, float precioBase) {
    this->id = id;
    this->tipoServicio = tipoServicio;
    this->precioBase = precioBase;
}

Servicio::~Servicio() {

}

int Servicio::getId() {
    return id;
}

string Servicio::getTipoServicio() {
    return tipoServicio;
}

float Servicio::getPrecioBase() {
    return precioBase;
}
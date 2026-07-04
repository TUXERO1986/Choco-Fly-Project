#include "Reserva.h"
Reserva::Reserva(string codigoUsuario, string nombreUsuario, int id) {
	this->codigoUsuario = codigoUsuario;
	this->nombreUsuario = nombreUsuario;
	this->id=id;
}
void Reserva::MostrarDatos() {}
string Reserva::getCodigoUsuario() { return codigoUsuario; }
string Reserva::getNombreUsuario() { return nombreUsuario; }
string Reserva::getTipoReserva() { return tipoReserva; }
void Reserva::setCodigoUsuario(string codigoUsuario) { this->codigoUsuario = codigoUsuario; }
void Reserva::setNombreUsuario(string nombreUsuario) { this->nombreUsuario = nombreUsuario; }
void Reserva::setTipoReserva(string tipoReserva) { this->tipoReserva = tipoReserva; }

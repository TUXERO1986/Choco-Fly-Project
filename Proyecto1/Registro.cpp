#include "Registro.h"

Registro::Registro(string nombre, string correo, string tipoUsuario, string accion, string fechaHora) {
    this->nombre = nombre;
    this->correo = correo;
    this->tipoUsuario = tipoUsuario;
    this->accion = accion;
    this->fechaHora = fechaHora;
}

Registro::~Registro() {}

string Registro::getNombre() { return nombre; }
string Registro::getCorreo() { return correo; }
string Registro::getTipoUsuario() { return tipoUsuario; }
string Registro::getAccion() { return accion; }
string Registro::getFechaHora() { return fechaHora; }

void Registro::setNombre(string nombre) { this->nombre = nombre; }
void Registro::setCorreo(string correo) { this->correo = correo; }
void Registro::setTipoUsuario(string tipoUsuario) { this->tipoUsuario = tipoUsuario; }
void Registro::setAccion(string accion) { this->accion = accion; }
void Registro::setFechaHora(string fechaHora) { this->fechaHora = fechaHora; }

void Registro::MostrarRegistro() {
    cout << "[" << fechaHora << "] " << tipoUsuario << ": " 
         << nombre << " (" << correo << ") -> " << accion << endl;
}
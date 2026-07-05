#include "Registro.h"
#include "Color.h"

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
    ColorUI::printGradient("[" + fechaHora + "] ", ColorUI::Paletas::dato, false, false);

    if (tipoUsuario == "Administrador" || tipoUsuario == "ADMIN") {
        ColorUI::printGradient("[ADMIN] " + nombre + " (" + correo + ") ", ColorUI::Paletas::rosa, false, false);
    } else if (tipoUsuario == "Usuario" || tipoUsuario == "USUARIO") {
        ColorUI::printGradient("[USUARIO] " + nombre + " (" + correo + ") ", ColorUI::Paletas::Register, false, false);
    } else {
        ColorUI::printGradient("[" + tipoUsuario + "] " + nombre + " (" + correo + ") ", ColorUI::Paletas::azul, false, false);
    }

    if (accion.find("Elimino") != string::npos || accion.find("Cancelo") != string::npos || accion.find("elimino") != string::npos || accion.find("cancelo") != string::npos) {
        ColorUI::printGradient("-> " + accion, ColorUI::Paletas::Alerta, false, true);
    } else if (accion.find("Agrego") != string::npos || accion.find("Registro") != string::npos || accion.find("Inicio") != string::npos || accion.find("agrego") != string::npos || accion.find("inicio") != string::npos) {
        ColorUI::printGradient("-> " + accion, ColorUI::Paletas::Exito, false, true);
    } else {
        ColorUI::printGradient("-> " + accion, ColorUI::Paletas::TemaPrincipal, false, true);
    }
}
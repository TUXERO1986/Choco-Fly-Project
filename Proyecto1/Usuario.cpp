#include "Usuario.h"
Usuario::Usuario(string nombre, string correo, string password, string codigo) {
	this->nombre = nombre;
	this->correo = correo;
	this->password = password;
	this->codigo = codigo;
}
void Usuario::MostrarDatosUsuarios() {
	cout << "Nombre: " << nombre << endl;
	cout << "Correo: " << correo << endl;
}
void Usuario::MostrarDatosAdmin() {
	cout << "Nombre: " << nombre << endl;
	cout << "Correo: " << correo << endl;
	cout << "Codigo: " << codigo << endl;
	cout << "Password: " << password << endl;
}
void Usuario::setCodigo(string codigo) { this->codigo = codigo; }
void Usuario::setNombre(string nombre) { this->nombre = nombre; }
void Usuario::setCorreo(string correo) { this->correo = correo; }
void Usuario::setPassword(string password) { this->password = password; }

string Usuario::getCorreo() { return correo; }
string Usuario::getNombre() { return nombre; }
string Usuario::getPassword() { return password; }
string Usuario::getCodigo() { return codigo; }

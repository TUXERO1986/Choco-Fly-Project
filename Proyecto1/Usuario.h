#pragma once
#include <iostream>
#include <string>
using namespace std;
class Usuario
{
private:
	string nombre;
	string correo;
	string password;
	string codigo;
public:
	Usuario(string nombre, string correo, string password, string codigo);
	void MostrarDatosUsuarios();
	void MostrarDatosAdmin();

	string getCodigo();
	string getNombre();
	string getCorreo();
	string getPassword();
	void setNombre(string nombre);
	void setCorreo(string correo);
	void setPassword(string password);
	void setCodigo(string codigo);
};


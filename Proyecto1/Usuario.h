#pragma once
#include "Reserva.h"
#include "Lista.h"
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
	Lista<Reserva*>* reservas;
public:
	Usuario(string nombre, string correo, string password, string codigo);
	~Usuario();
	void MostrarDatos();

	string getCodigo();
	string getNombre();
	string getCorreo();
	string getPassword();
	void setNombre(string nombre);
	void setCorreo(string correo);
	void setPassword(string password);
	void setCodigo(string codigo);

	Lista<Reserva*>* getReservas();
	void setReservas(Lista<Reserva*>* reservas);
};


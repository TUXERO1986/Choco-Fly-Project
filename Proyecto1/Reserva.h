#pragma once
#include <iostream>
#include <string>
using namespace std;
class Reserva
{
protected:
	string tipoReserva;
	string codigoUsuario;
	string nombreUsuario;
	int id;
public:
	Reserva(string codigoUsuario, string nombreUsuario,int id);
	virtual void MostrarDatos();
	virtual string aTextoArchivo() = 0;
	string getCodigoUsuario();
	string getNombreUsuario();
	string getTipoReserva();
	virtual float getPrecioTotal() = 0;
	void setCodigoUsuario(string codigoUsuario);
	void setNombreUsuario(string nombreUsuario);
	void setTipoReserva(string tipoReserva);
	int getId();

};


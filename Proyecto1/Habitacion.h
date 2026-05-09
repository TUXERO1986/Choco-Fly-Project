#pragma once
#include <iostream>
using namespace std;
class Habitacion
{
private:
	int numero;
	int tipo;
	int disponible;
public:
	Habitacion(int, int);

	void MostrarHabitacion();
	int getNumero();
	int getTipo();
	bool getDisponible();

	void setDisponible(bool);
	void setNumero(int);
	void setTipo(int);
};


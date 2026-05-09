#pragma once
#include <iostream>
using namespace std;
class Habitacion
{
private:
	int numero;
	int disponible;
public:
	Habitacion(int);

	void MostrarHabitacion();
	int getNumero();
	bool getDisponible();

	void setDisponible(bool);
	void setNumero(int);
};


#pragma once
#include <iostream>
using namespace std;
class Asiento
{
private:
	int numero;
	int clase;
	bool disponible;
public:
	Asiento(int,int);
	void MostraAsiento();
	int getNumero();
	int getClase();
	bool getDisponible();

	void setDisponible(bool);
	void setNumero(int);
	void setClase(int);
};


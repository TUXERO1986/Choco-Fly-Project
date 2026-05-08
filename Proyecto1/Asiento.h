#pragma once
#include <iostream>
using namespace std;
class Asiento
{
private:
	int numero;
	bool disponible;
public:
	Asiento(int);
	void MostraAsiento();
	int getNumero();
	bool getDisponible();

	void setDisponible(bool);
	void setNumero(int);
};


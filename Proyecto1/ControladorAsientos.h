#pragma once
#include "Asiento.h"
#include "Lista.h"
class ControladorAsientos
{
private:
	Lista<Asiento*>* asientos;
public:
	ControladorAsientos();
	void MostrarAsientos();
	void GenerarAsientos();
	Lista<Asiento*>* getAsientos();
	void setAsientos(Lista<Asiento*>* asientos);
};


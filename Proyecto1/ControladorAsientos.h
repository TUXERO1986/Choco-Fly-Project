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
	bool VerificarAsiento(int numeroAsiento);
	string ObtenerEstadoAsientosString();
	void CargarEstadoAsientosString(string estado);
	Lista<Asiento*>* getAsientos();
	void setAsientos(Lista<Asiento*>* asientos);
};


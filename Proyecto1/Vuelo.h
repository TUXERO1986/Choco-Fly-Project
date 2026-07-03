#pragma once
#include "Asiento.h"
#include "Lista.h"
class Vuelo
{
private:
	string origen;
	string destino;
	string escalas;
	string fecha;
	int id;
	float distancia;
	Lista<Asiento*>* asientos;
public:
	Vuelo(string o, string d, string e, string f, float distancia,int id);

	void MostrarVuelo();
	void MostrarAsientos();
	string GetFechaPorDestinoYOrigen(string origen,string destino);

	string getOrigen();
	string getDestino();
	string getEscalas();
	string getFecha();
	float getDistancia();
	int getId();

	float getPrecioBase();
	void setOrigen(string o);
	void setDestino(string d);
	void setEscalas(string e);
	void setFecha(string f);
	void setDistancia(float distancia);	

	void GenerarAsientos();
	bool VerificarAsiento(int numeroAsiento);
	string ObtenerEstadoAsientosString();
	void CargarEstadoAsientosString(string estado);
	Lista<Asiento*>* getAsientos();
	void setAsientos(Lista<Asiento*>* asientos);

};
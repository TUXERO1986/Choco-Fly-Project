#pragma once
#include "Vuelo.h"
#include "ControladorRutas.h"
#include <ctime>
#include <functional>
class ControladorVuelos
{
private:
ControladorArchivos* controladorArchivos;
ControladorRutas* controladorRutas;
Lista<Vuelo*>* vuelos;
function<int(string)> ObtenerMes;
function<int(string)> ObtenerDia;
float CalcularPrecio(Lista<Vuelo*>*, int);
float CalcularDistancia(Lista<Ruta*>* , int );
public:
	ControladorVuelos();
	~ControladorVuelos();
	bool BuscarCadenaVuelos(int indiceRuta, Lista<Ruta*>*& rutas, Lista<Vuelo*>*& cadenaActual);
	void MostrarVuelos();
	void AgregarNuevoVuelo(string origen, string destino, string escalas, string fecha, float precio);
	void GenerarVuelos(int contador);
	void GenerarVuelosConEscala(string origen,string destino);
};


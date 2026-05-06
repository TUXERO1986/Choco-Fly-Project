#pragma once
#include "ControladorArchivos.h"
#include "Color.h"
class ControladorVuelos
{
private:
Lista<Vuelo*>* vuelos;
function<int(string)> ObtenerMes;
function<int(string)> ObtenerDia;
ControladorArchivos* controladorArchivosVuelos;
float CalcularPrecio(Lista<Vuelo*>*, int);
float CalcularDistancia(Lista<Ruta*>* , int );
public:
	ControladorVuelos();
	~ControladorVuelos();
	void BuscarCadenaVuelos(int indiceRuta, Lista<Ruta*>* rutas,
	Lista<Vuelo*>* cadenaActual, Lista<Lista<Vuelo*>*>* todasLasCadenas);
	void MostrarVuelos();
	void AgregarNuevoVuelo(string origen, string destino, string escalas, string fecha,float distancia, float precio);
	void GenerarVuelos(int contador, Lista<Ruta*>* rutas);
	void GenerarVuelosConEscala(string origen,string destino, Lista<Ruta*>* rutas);
	Vuelo* ObtenerVueloPorPosicion(int pos);
	Lista<Vuelo*>* getVuelos();	
};


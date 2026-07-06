#pragma once
#include "ControladorArchivos.h"
#include "ArbolAVL.h"
#include "ArbolAVLMiltiClave.h"
#include "Color.h"
class ControladorVuelos
{
private:
Lista<Vuelo*>* vuelos;
ArbolAVL<Vuelo*>* vuelosMenorPrecio;
ArbolAVLMultiClave<Vuelo*, string>* indiceVuelosPorOrigen;
function<int(string)> ObtenerMes;
function<int(string)> ObtenerDia;
ControladorArchivos* controladorArchivosVuelos;
public:
ControladorVuelos();
~ControladorVuelos();
void BuscarCadenaVuelos(int indiceRuta, Lista<Ruta*>* rutas,
	Lista<Vuelo*>* cadenaActual, Lista<Lista<Vuelo*>*>* todasLasCadenas);
	void MostrarVuelos();
	void FiltrarVuelosPorOrigenDestino(string origen, string destino);
	bool VerificarVueloDirecto(string origen, string destino);
	void AgregarNuevoVuelo(string origen, string destino, string escalas, string fecha,float distancia);
	void GenerarVuelos(int contador, Lista<Ruta*>* rutas);
	bool GenerarVuelosConEscala(string origen,string destino, Lista<Ruta*>* rutas);
	Vuelo* ObtenerVueloPorPosicion(int pos);
	Lista<Vuelo*>* getVuelos();	
	ArbolAVL<Vuelo*>* getVuelosMenorPrecio();
};


#pragma once
#include "ControladorArchivos.h"
#include "Cola.h"
struct EstadoRuta {
    int idCiudadActual;
    string recorrido; 
    int cantidadSaltos;    

    EstadoRuta(int id, std::string rec, int saltos) {
        idCiudadActual = id;
        recorrido = rec;
        cantidadSaltos = saltos;
    }
};
class ControladorRutas
{
private:
	    ControladorArchivos* controladorArchivos;
		Lista<Ruta*>* rutas;
		Lista<Lista<int>*>* conexiones;
		Lista<CiudadId*>* MapaCiudades;

public:
    ControladorRutas();
	string BuscarRutaMasCorta(string origen, string destino);
	void AgregarNuevaRuta(string origen, string destino, string aerolinea, float precio, float distancia);
	void MostrarTodasLasRutas();
};


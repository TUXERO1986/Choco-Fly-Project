#pragma once
#include "ControladorArchivos.h"
#include "Cola.h"
class ControladorRutas
{
private:
	ControladorArchivos* controladorArchivos;
	Lista<Ruta*>* rutas;
	Lista<Lista<int>*>* conexiones;
	Lista<CiudadID*>* MapaCiudades;
    function<size_t(Lista<CiudadID*>*, string)> ObtenerIdCiudad;
 struct EstadoRuta {
   int idCiudadActual;
   int cantidadSaltos;
   Lista<Ruta*>* vuelosTomados; 

   EstadoRuta(int id, int saltos) {
       idCiudadActual = id;
       cantidadSaltos = saltos;
       vuelosTomados = new Lista<Ruta*>();
   }

   EstadoRuta(int id, int saltos, Lista<Ruta*>* vuelosAnteriores, Ruta* nuevoVuelo) {
       idCiudadActual = id;
       cantidadSaltos = saltos;
       vuelosTomados = new Lista<Ruta*>();

       for (unsigned int i = 0; i < vuelosAnteriores->longitud(); i++) {
           vuelosTomados->agregaFinal(vuelosAnteriores->obtenerPos(i));
       }

       if (nuevoVuelo != nullptr) {
           vuelosTomados->agregaFinal(nuevoVuelo);
       }
   }
    };

public:
    ControladorRutas();
	Lista<Ruta*>* BuscarRutaMasCorta(string origen, string destino);
	void AgregarNuevaRuta(string origen, string destino, float distancia);
	void MostrarRutas();
	Lista<Ruta*>* getRutas();
	Lista<Lista<int>*>* getConexiones();
	Lista<CiudadID*>* getMapaCiudades();
};


#pragma once
#include "ControladorArchivos.h"
#include "Cola.h"
#include "Grafo.h"
#include "ArbolAVLClave.h"
class ControladorRutas
{
private:
	ControladorArchivos* controladorArchivos;
	Lista<Ruta*>* rutas;
    CGrafo<string>* grafoRutas;
	Lista<Lista<int>*>* conexiones;
	Lista<CiudadID*>* MapaCiudades;
    ArbolAVLClave<CiudadID*, string>* indiceCiudadesPorNombre;
    ArbolAVLClave<CiudadID*, string>* indiceCiudades;
    function<int(Lista<CiudadID*>*, string)> ObtenerIdCiudad;
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
    ~ControladorRutas();
	Lista<Ruta*>* BuscarRutaMasCorta(string origen, string destino);
	void AgregarNuevaRuta(string origen, string destino, float distancia);
	void MostrarRutas();
	Lista<Ruta*>* getRutas();
    int ObtenerIdCiudadPorNombre(string nombre);

	Lista<Lista<int>*>* getConexiones();
	Lista<CiudadID*>* getMapaCiudades();
};


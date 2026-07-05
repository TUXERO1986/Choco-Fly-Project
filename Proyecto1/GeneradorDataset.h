#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "ControladorArchivos.h"
#include "ControladorHoteles.h"
#include "ControladorPaquetes.h"
#include "ControladorVuelos.h"
#include "Ruta.h"

using namespace std;

class GeneradorDataset {
private:
    static const int CANT_HOTELES_NOMBRES = 10;
    string nombresHoteles[CANT_HOTELES_NOMBRES];

    string GenerarFechaAleatoria();
    string GenerarEstadoAsientosOHabitaciones(int cantidad);

public:
    GeneradorDataset();
    ~GeneradorDataset();

void GenerarVuelosAleatorios(int cantidad, Lista<Ruta*>* rutas, ControladorVuelos* ctrlVuelos);
void GenerarHotelesAleatorios(int cantidad, Lista<Ruta*>* rutas, ControladorHoteles* ctrlHoteles);
void GenerarPaquetesAleatorios(int cantidad, Lista<Ruta*>* rutas, ControladorPaquetes* ctrlPaquetes, Lista<Vuelo*>* listaVuelos, Lista<Hotel*>* listaHoteles);

void GenerarTodo(int cantVuelos, int cantHoteles, int cantPaquetes, 
                 Lista<Ruta*>* rutas, 
                 ControladorVuelos* cv, 
                 ControladorHoteles* ch, 
                 ControladorPaquetes* cp);
};
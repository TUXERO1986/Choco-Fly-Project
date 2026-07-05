#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Lista.h"
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

    void GenerarVuelosAleatorios(int cantidad, Lista<Ruta*>* rutas);
    void GenerarHotelesAleatorios(int cantidad, Lista<Ruta*>* rutas);
    void GenerarPaquetesAleatorios(int cantidad, Lista<Ruta*>* rutas);
    
    void GenerarTodo(int cantVuelos, int cantHoteles, int cantPaquetes, Lista<Ruta*>* rutas);
};
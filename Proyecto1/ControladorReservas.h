#pragma once
#include "Lista.h"
#include "Reserva.h"

#include "ControladorArchivos.h" 
#include <iostream>
#include <string>

using namespace std;

class ControladorReservas
{
private:
    Lista<Reserva*>* reservasTotales;
	ControladorArchivos* controladorArchivos;
public:
    ControladorReservas();
    ~ControladorReservas();

    void AgregarReserva(Reserva* nuevaReserva);
    Lista<Reserva*>* getReservasTotales();

    void MostrarReservas();

    float CalcularIngresosTotales();
};


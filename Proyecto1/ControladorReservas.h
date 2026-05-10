#pragma once
#include "Lista.h"
#include "Reserva.h"
// Incluye aquí tu ControladorArchivos cuando lo vayas a conectar
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


#pragma once
#include "Lista.h"
#include "Reserva.h"
#include "ArbolAVLClave.h"
#include "ControladorArchivos.h" 
#include <iostream>
#include <string>

using namespace std;

class ControladorReservas
{
private:
    Lista<Reserva*>* reservasTotales;
	ControladorArchivos* controladorArchivos;
    ArbolAVLClave<Reserva*, int>* indiceReservasPorID;
public:
    ControladorReservas();
    ~ControladorReservas();

    void AgregarReserva(Reserva* nuevaReserva);
    Lista<Reserva*>* getReservasTotales();

    Reserva* BuscarReservaPorID(int id);
    void MostrarReservas();

    float CalcularIngresosTotales();
};


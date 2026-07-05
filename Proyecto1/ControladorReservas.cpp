#include "ControladorReservas.h"
ControladorReservas::ControladorReservas() {
    reservasTotales = new Lista<Reserva*>();
	controladorArchivos = new ControladorArchivos("Reservas.txt");
    controladorArchivos->LeerArchivoReservas(reservasTotales);
    indiceReservasPorID = new ArbolAVLClave<Reserva*, int>([](Reserva* r) {
        return r->getId(); 
    });
}

ControladorReservas::~ControladorReservas() {
    for (int i = 0; i < reservasTotales->longitud(); i++) {
        delete reservasTotales->obtenerPos(i);
    }
    delete reservasTotales;
    delete controladorArchivos;
    delete indiceReservasPorID;
}

void ControladorReservas::AgregarReserva(Reserva* nuevaReserva) {
    if (nuevaReserva != nullptr) {

        reservasTotales->agregaFinal(nuevaReserva);

        controladorArchivos->GuardarDatoArchivoReservas(nuevaReserva);
        indiceReservasPorID->Insertar(nuevaReserva);
        cout << "Reserva registrada y guardada con exito en el sistema." << endl;
    }
}
Reserva* ControladorReservas::BuscarReservaPorID(int id) {
    // Búsqueda en el Árbol AVL: O(log n) en lugar de O(n)
    return indiceReservasPorID->Buscar(id);
}

Lista<Reserva*>* ControladorReservas::getReservasTotales() {
    return reservasTotales;
}


void ControladorReservas::MostrarReservas() {
    cout << "\n=== REGISTRO GLOBAL DE VENTAS (ADMINISTRADOR) ===" << endl;

    if (reservasTotales->longitud() == 0) {
        cout << "El sistema no tiene reservas registradas." << endl;
        return;
    }

    for (int i = 0; i < reservasTotales->longitud(); i++) {
        cout << "\nReserva #" << (i + 1) << ":" << endl;
        cout << endl;
        reservasTotales->obtenerPos(i)->MostrarDatos();
        cout << endl;
    }
    cout << "===================================================" << endl;
}



float ControladorReservas::CalcularIngresosTotales() {
    float total = 0;

    for (int i = 0; i < reservasTotales->longitud(); i++) {
        total += reservasTotales->obtenerPos(i)->getPrecioTotal();
    }
    return total;
}
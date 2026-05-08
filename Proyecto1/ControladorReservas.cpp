#include "ControladorReservas.h"
ControladorReservas::ControladorReservas() {
    reservasTotales = new Lista<Reserva*>();
	controladorArchivos = new ControladorArchivos("Reservas.txt");
    controladorArchivos->LeerArchivoReservas(reservasTotales);
}

ControladorReservas::~ControladorReservas() {
    for (int i = 0; i < reservasTotales->longitud(); i++) {
        delete reservasTotales->obtenerPos(i);
    }
    delete reservasTotales;
    delete controladorArchivos;
}

void ControladorReservas::AgregarReserva(Reserva* nuevaReserva) {
    if (nuevaReserva != nullptr) {

        reservasTotales->agregaFinal(nuevaReserva);

        controladorArchivos->GuardarDatoArchivoReservas(nuevaReserva);

        cout << "Reserva registrada y guardada con exito en el sistema." << endl;
    }
}

Lista<Reserva*>* ControladorReservas::getReservasTotales() {
    return reservasTotales;
}

void ControladorReservas::MostrarReservasUsuario(string codigoUsuario) {
    cout << "\n=== HISTORIAL DE RESERVAS DEL USUARIO: " << codigoUsuario << " ===" << endl;
    int contador = 0;

    for (int i = 0; i < reservasTotales->longitud(); i++) {
        Reserva* r = reservasTotales->obtenerPos(i);

        if (r->getCodigoUsuario() == codigoUsuario) {
            r->MostrarReserva(); 
            contador++;
        }
    }

    if (contador == 0) {
        cout << "No tienes ninguna reserva registrada." << endl;
    }
    cout << "===================================================" << endl;
}
void ControladorReservas::MostrarReservasAdmin() {
    cout << "\n=== REGISTRO GLOBAL DE VENTAS (ADMINISTRADOR) ===" << endl;

    if (reservasTotales->longitud() == 0) {
        cout << "El sistema no tiene reservas registradas." << endl;
        return;
    }

    for (int i = 0; i < reservasTotales->longitud(); i++) {
        cout << "\nReserva #" << (i + 1) << ":" << endl;
        reservasTotales->obtenerPos(i)->MostrarReserva();
    }
    cout << "===================================================" << endl;
}

void ControladorReservas::FiltrarReservasPorTipo(string tipoBusqueda) {
    cout << "\n=== FILTRANDO VENTAS POR TIPO: " << tipoBusqueda << " ===" << endl;
    int contador = 0;

    for (int i = 0; i < reservasTotales->longitud(); i++) {
        Reserva* r = reservasTotales->obtenerPos(i);

        if (r->getTipoReserva() == tipoBusqueda) {
            r->MostrarReserva();
            contador++;
        }
    }

    if (contador == 0) {
        cout << "No se encontraron ventas de la categoria " << tipoBusqueda << "." << endl;
    }
}

float ControladorReservas::CalcularIngresosTotales() {
    float total = 0;

    for (int i = 0; i < reservasTotales->longitud(); i++) {
        total += reservasTotales->obtenerPos(i)->getPrecioTotal();
    }
    return total;
}
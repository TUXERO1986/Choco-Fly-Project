#include "ControladorRegistros.h"

ControladorRegistros::ControladorRegistros() {
    registros = new Lista<Registro*>();
}

ControladorRegistros::~ControladorRegistros() {
    for (uint i = 0; i < registros->longitud(); i++) {
        delete registros->obtenerPos(i);
    }
    delete registros;
}

void ControladorRegistros::AgregarRegistro(Registro* nuevoRegistro) {
    if (nuevoRegistro != nullptr) {
        registros->agregaFinal(nuevoRegistro);
    }
}

void ControladorRegistros::MostrarDatos() {
    if (registros->longitud() == 0) {
        cout << "\n[!] El historial de acciones se encuentra vacio." << endl;
        return;
    }

    cout << "\n=========================================================" << endl;
    cout << "           HISTORIAL DE ACCIONES (MÁS RECIENTES)         " << endl;
    cout << "=========================================================" << endl;

    int ultimoIndice = static_cast<int>(registros->longitud()) - 1;

    for (int i = ultimoIndice; i >= 0; i--) {
        registros->obtenerPos(i)->MostrarRegistro();
    }
    cout << "=========================================================" << endl;
}

Lista<Registro*>* ControladorRegistros::getRegistros() {
    return registros;
}
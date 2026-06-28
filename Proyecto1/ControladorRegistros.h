#pragma once
#include "Lista.h"
#include "Registro.h"

class ControladorRegistros {
private:
    Lista<Registro*>* registros;

public:
    ControladorRegistros();
    ~ControladorRegistros();

    void AgregarRegistro(Registro* nuevoRegistro);
    void MostrarDatos();

    Lista<Registro*>* getRegistros();
};
#pragma once
#include "ControladorArchivos.h"
#include "Registro.h"

class ControladorRegistros {
private:
    Lista<Registro*>* registros;
public:
    ControladorRegistros();
    ~ControladorRegistros();

    void AgregarRegistro(string nombre, string correo, string tipoUsuario, string accion, string fechaHora);
    void MostrarDatos();

    Lista<Registro*>* getRegistros();
};
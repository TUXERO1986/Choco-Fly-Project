#pragma once
#include "ControladorArchivos.h"
#include "Registro.h"
#include <iomanip>
#include <ctime>
class ControladorRegistros {
private:
    Lista<Registro*>* registros;
    string ObtenerFechaHoraActual();
public:
    ControladorRegistros();
    ~ControladorRegistros();

    void AgregarRegistro(string nombre, string correo, string tipoUsuario, string accion);
    void MostrarDatos();

    Lista<Registro*>* getRegistros();
};
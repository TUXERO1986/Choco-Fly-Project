#pragma once
#include "ControladorPrincipal.h"
#include "Color.h"
#include <iostream>

class AdminPantallas {
private:
    ControladorPrincipal* principal;

    void AgregarVuelos();
    void AgregarPaquetes();
    void AgregarHoteles();
    void EliminarVuelos();
    void EliminarPaquetes();
    void EliminarHoteles();

public:
    AdminPantallas(ControladorPrincipal* ptrPrincipal);

    void MenuAdmin();
};
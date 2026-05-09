#pragma once
#include "ControladorPrincipal.h"
#include "Color.h"

#include <conio.h>

class AdminPantallas {
private:
    ControladorPrincipal* principal;
    int LeerOpcion(); 

public:
    AdminPantallas(ControladorPrincipal* ptrPrincipal);

    void MenuPrincipalAdmin();
    void MenuReportes();
    void MenuMantenimiento();
    void GenerarDatosAleatorios();
};
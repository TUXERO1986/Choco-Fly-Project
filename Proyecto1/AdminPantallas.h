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
	void FiltroRutas();
    void MenuFiltrosReservas();
    void MenuFiltrosVuelos();
    void MenuFiltrosPaquetes();
    void MenuFiltrosHoteles();
    void MenuFiltrosUsuarios();
    void MenuMantenimiento();
    void GenerarDatosAleatorios();
    void MenuAgregar();
	void MenuEliminar();
};
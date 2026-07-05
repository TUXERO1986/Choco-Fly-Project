#pragma once
#include "GestionPantallas.h"
#ifdef _WIN32
    #include <conio.h>
#else
    #include <iostream>
    #include <unistd.h> 
#endif

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
#pragma once
#include "GestionPantallas.h"
#ifdef _WIN32
    // Todo lo que esté aquí SOLO se compilará en las PCs de tus amigos (Windows)
    #include <conio.h>
#else
    // Todo lo que esté aquí SOLO se compilará en tu PC (Linux/Mac)
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
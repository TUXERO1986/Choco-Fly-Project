#pragma once
#include "Lista.h"
#include "Color.h"
#include "ControladorPrincipal.h"
#include "Usuario.h"
#include <conio.h>

class GestionPantallas {
private:
    ControladorPrincipal* principal;
    Usuario* userActual; 

public:
    GestionPantallas(ControladorPrincipal* ptrPrincipal, Usuario* ptrUsuario);

    int LeerOpcion(); 
    void Menuprincipal();
    void MenuFiltrosReservas();
    void MenuFiltrosVuelos();
    void MenuFiltrosPaquetes();
    void MenuFiltrosHoteles();
    void MenuCatalogos();
    void MenuReservas();
    void MenuDatosUsuario();
    void MenuCancelarReserva();
    void MenuCalificacionHotel();
    void MenuReservaHotel();
    void MenuReservaVuelo();
    void MenuReservaPaquete();
    void HistorialReservas();
};
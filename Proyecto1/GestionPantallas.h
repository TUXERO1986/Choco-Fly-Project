#pragma once
#include "Lista.h"
#include "Color.h"
#include "ControladorPrincipal.h"
#include "Usuario.h"
#include <conio.h>

class GestionPantallas {
private:
    ControladorPrincipal* principal;
    Usuario* userActual; // Guardamos la sesion del usuario

public:
    GestionPantallas(ControladorPrincipal* ptrPrincipal, Usuario* ptrUsuario);

    int LeerOpcion(); // Funcion anti-crasheos
    void Menuprincipal();
    void VuelosRyan();
    void ReservarHospedaje();
    void GestionTickets();
    void CatalogoPaquetes();
    void HistorialReservas();
};
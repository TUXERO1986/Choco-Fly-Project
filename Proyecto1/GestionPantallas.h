#pragma once
#include "Lista.h"
#include "Color.h"
#include "ControladorPrincipal.h"
#include "conio.h"
#include "ControladorPrincipal.h"

class GestionPantallas {
private:
    // El "jefe" se guarda aquí, a nivel de clase
    ControladorPrincipal* principal;

public:
    // Constructor: aquí lo recibes UNA sola vez
    GestionPantallas(ControladorPrincipal* ptrPrincipal);

    // Tus pantallas ya NO necesitan recibir nada por parámetro
    void Menuprincipal(GestionPantallas* ui);
    void VuelosRyan();
    void ReservarHospedaje();
    void GestionTickets();
    void CatalogoPaquetes();
    // ... y todas las demas ...
};
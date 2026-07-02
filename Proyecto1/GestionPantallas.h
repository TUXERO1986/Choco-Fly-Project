#pragma once
#include "Color.h"
#include "ControladorPrincipal.h"
#include "Pila.h" // Incluimos la pila

// Identificadores únicos para cada pantalla
enum PantallaID {
    PANTALLA_PRINCIPAL = 1,
    PANTALLA_CATALOGOS,
    PANTALLA_RESERVAS,
    PANTALLA_DATOS_USUARIO,
    PANTALLA_HISTORIAL_RESERVAS,
    PANTALLA_CANCELAR_RESERVA,
    PANTALLA_CALIFICAR_HOTEL,
    PANTALLA_FILTROS_VUELOS,
    PANTALLA_FILTROS_HOTELES,
    PANTALLA_FILTROS_PAQUETES,
    PANTALLA_FILTROS_RESERVAS,
    PANTALLA_RESERVA_VUELO,
    PANTALLA_RESERVA_HOTEL,
    PANTALLA_RESERVA_PAQUETE
};

class GestionPantallas {
private:
    ControladorPrincipal* principal;
    Usuario* userActual; 
    
    // NUEVO: La pila que gestionará el historial de navegación
    Pila<PantallaID>* historialPantallas;

public:
    GestionPantallas(ControladorPrincipal* ptrPrincipal, Usuario* ptrUsuario);
    ~GestionPantallas(); // Agregamos destructor para limpiar la pila

    int LeerOpcion(); 
    void DibujarHeader(string ruta);
    
    // NUEVO: El motor que reemplaza los bucles
    void IniciarMotorNavegacion();

    // Las funciones de pantalla ya no tendrán do-while
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
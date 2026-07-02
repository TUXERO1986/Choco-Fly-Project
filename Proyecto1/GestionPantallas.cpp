#include "GestionPantallas.h"
#include <iomanip>

GestionPantallas::GestionPantallas(ControladorPrincipal* ptrPrincipal, Usuario* ptrUsuario) {
    principal = ptrPrincipal;
    userActual = ptrUsuario;
    historialPantallas = new Pila<PantallaID>(); // Inicializamos la pila
}

GestionPantallas::~GestionPantallas() {
    delete historialPantallas;
}

int GestionPantallas::LeerOpcion() {
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(1000, '\n');
        ColorUI::printGradient("\tError: Ingresa un numero valido: ", Alerta, false, false);
    }
    cin.ignore(1000, '\n');
    return x;
}

void GestionPantallas::DibujarHeader(string ruta) {
    LimpiarConsola();
    ColorUI::printGradient("================================================================================", Paletas::TemaPrincipal, false);
    if (userActual != nullptr) {
        ColorUI::printGradient("  [USER] Usuario: " + userActual->getNombre() + "  |  [MAIL] " + userActual->getCorreo(), Paletas::Exito, false);
    } else {
        ColorUI::printGradient("  [USER] Usuario: Invitado (No Logueado)", Paletas::Alerta, false);
    }
    ColorUI::printGradient("  [PATH] Ruta: " + ruta, Paletas::azul, false);
    ColorUI::printGradient("================================================================================\n", Paletas::TemaPrincipal, false);
}

// ====================================================================
// EL MOTOR CENTRAL: Reemplaza a todos los do-while anidados
// ====================================================================
void GestionPantallas::IniciarMotorNavegacion() {
    // La primera pantalla al iniciar sesión es el menú principal
    historialPantallas->apilar(PANTALLA_PRINCIPAL);

    // El bucle principal del programa. Se ejecuta mientras haya pantallas en la pila.
    while (!historialPantallas->estaVacia()) {
        PantallaID pantallaActual = historialPantallas->verTope();

        switch (pantallaActual) {
            case PANTALLA_PRINCIPAL: Menuprincipal(); break;
            case PANTALLA_CATALOGOS: MenuCatalogos(); break;
            case PANTALLA_RESERVAS: MenuReservas(); break;
            case PANTALLA_DATOS_USUARIO: MenuDatosUsuario(); break;
            case PANTALLA_HISTORIAL_RESERVAS: HistorialReservas(); break;
            case PANTALLA_CANCELAR_RESERVA: MenuCancelarReserva(); break;
            case PANTALLA_CALIFICAR_HOTEL: MenuCalificacionHotel(); break;
            case PANTALLA_FILTROS_VUELOS: MenuFiltrosVuelos(); break;
            case PANTALLA_FILTROS_HOTELES: MenuFiltrosHoteles(); break;
            case PANTALLA_FILTROS_PAQUETES: MenuFiltrosPaquetes(); break;
            case PANTALLA_FILTROS_RESERVAS: MenuFiltrosReservas(); break;
            case PANTALLA_RESERVA_VUELO: MenuReservaVuelo(); break;
            case PANTALLA_RESERVA_HOTEL: MenuReservaHotel(); break;
            case PANTALLA_RESERVA_PAQUETE: MenuReservaPaquete(); break;
            default:
                historialPantallas->desapilar();
                break;
        }
    }
}

// ====================================================================
// MENÚS DE NAVEGACIÓN (Sin bucles)
// ====================================================================

void GestionPantallas::Menuprincipal() {
    DibujarHeader("Inicio");
    cout << BLINK;
    ColorUI::printGradient(chocofly, TemaPrincipal, false);
    cout << RESET;
    ColorUI::printGradient("\n\n\t\t\t\t\t[1] CATALOGOS DE SERVICIOS", Exito, false);
    ColorUI::printGradient("\n\t\t\t\t\t[2] RESERVAR UN SERVICIO", Exito, false);
    ColorUI::printGradient("\n\t\t\t\t\t[3] VERIFICAR MIS DATOS", Exito, false);
    ColorUI::printGradient("\n\t\t\t\t\t[4] MI HISTORIAL DE RESERVAS", Exito, false);
    ColorUI::printGradient("\n\t\t\t\t\t[5] CANCELAR RESERVA", Exito, false);
    ColorUI::printGradient("\n\t\t\t\t\t[6] CALIFICAR HOTEL", Exito, false);
    ColorUI::printGradient("\n\t\t\t\t\t[7] CREDITOS", Exito, false);
    ColorUI::printGradient("\n\t\t\t\t\t[0] Cerrar Sesion", Alerta, false);

    char opcion = _getch();

    switch (opcion) {
        case '1': historialPantallas->apilar(PANTALLA_CATALOGOS); break;
        case '2': historialPantallas->apilar(PANTALLA_RESERVAS); break;
        case '3': historialPantallas->apilar(PANTALLA_DATOS_USUARIO); break;
        case '4': historialPantallas->apilar(PANTALLA_HISTORIAL_RESERVAS); break;
        case '5': historialPantallas->apilar(PANTALLA_CANCELAR_RESERVA); break;
        case '6': historialPantallas->apilar(PANTALLA_CALIFICAR_HOTEL); break;
        case '7': LimpiarConsola(); creditos(); break; // Creditos no es una pantalla completa, solo muestra y vuelve
        case '0':
            LimpiarConsola();
            ColorUI::printGradient("Cerrando sesion...", Alerta, false);
            historialPantallas->desapilar(); // Vacia la pila, cerrando el bucle del motor
            break;
        default: cout << "Opcion no valida" << endl; break;
    }
}

void GestionPantallas::MenuCatalogos(){
    DibujarHeader("Inicio > Catalogo de Servicios");
    ColorUI::printGradient("\n================CATALOGO DE SERVICIOS==============", Exito, false);
    ColorUI::printGradient("\n[1] CATALOGO VUELOS DISPONIBLES", Exito, false);
    ColorUI::printGradient("\n[2] CATALOGO DE HOTELES DISPONIBLES", Exito, false);
    ColorUI::printGradient("\n[3] CATALOGO DE PQUETES DISPONIBLES", Exito, false);
    ColorUI::printGradient("\n[0] SALIR", Exito, false);
    
    char opcion = _getch();
    switch (opcion) {
        case '1': historialPantallas->apilar(PANTALLA_FILTROS_VUELOS); break;
        case '2': historialPantallas->apilar(PANTALLA_FILTROS_HOTELES); break;
        case '3': historialPantallas->apilar(PANTALLA_FILTROS_PAQUETES); break;
        case '0': historialPantallas->desapilar(); break; // Regresa al Menu Principal
    }
}

void GestionPantallas::MenuFiltrosVuelos() {
    DibujarHeader("Inicio > Catalogo > Vuelos");
    ColorUI::printGradient("\n================FILTROS VUELOS==============", Exito, false);
    ColorUI::printGradient("\n[1] VUELOS POR ORIGEN", Exito, false);
    ColorUI::printGradient("\n[2] VUELOS POR DESTINO", Exito, false);
    ColorUI::printGradient("\n[3] VUELOS POR FECHA", Exito, false);
    ColorUI::printGradient("\n[4] VUELOS POR PRESUPUESTO", Exito, false);
    ColorUI::printGradient("\n[5] VUELOS DE POR PRECIO (MAYOR A MENOR)", Exito, false);
    ColorUI::printGradient("\n[6] VER TODOS LOS VUELOS", Exito, false);
    ColorUI::printGradient("\n[0] SALIR", Exito, false);
    
    char opcion = _getch();
    switch (opcion) {
        case '1': {
            DibujarHeader("Inicio > Catalogo > Vuelos > Por Origen");
            vector<string> origenes;
            Lista<Vuelo*>* vuelos = principal->getControladorVuelos()->getVuelos();
            for(int i=0; i<vuelos->longitud(); i++){
                string o = vuelos->obtenerPos(i)->getOrigen();
                bool existe = false;
                for(string& org : origenes) { if(org == o) existe = true; }
                if(!existe) origenes.push_back(o);
            }
            if (origenes.empty()) { ColorUI::Alertas::MostrarInfo("No hay vuelos disponibles."); pausarConsola(); break; }
            ColorUI::printGradient("\n================ SELECCIONE ORIGEN ================\n", Paletas::TemaPrincipal, false);
            for(size_t i=0; i<origenes.size(); i++) {
                cout << " [" << i+1 << "] " << left << setw(20) << origenes[i];
                if((i+1)%3==0) cout << "\n";
            }
            cout << "\n\n> Ingrese opcion: ";
            int sel = LeerOpcion();
            if (sel > 0 && sel <= origenes.size()) {
                principal->FitrarVuelosPorOrigen(origenes[sel-1]);
            } else {
                ColorUI::Alertas::MostrarError("Opcion invalida.");
            }
            pausarConsola();
            break;
        }
        case '6': {
            principal->MostrarVuelos();
            break;
        }
        case '0': {
            historialPantallas->desapilar(); // Regresa al Menu Catalogos
            break;
        }
        // ... (Agrega el resto de los cases igual que antes, pero sin el return/break que rompa bucles)
    }
}

// ====================================================================
// PANTALLAS DE ACCIÓN LINEAL (Se desapilan solas al terminar)
// ====================================================================

void GestionPantallas::MenuDatosUsuario(){
    DibujarHeader("Inicio > Mis Datos");
    ColorUI::printGradient("\n\t\t\t\t\tDATOS DEL USUARIO ACTUAL\n", Exito, false);
    principal->FiltrarUsuarioPorCodigo(userActual->getCodigo()); 
    pausarConsola();
    
    // Al terminar de ver los datos, sacamos esta pantalla de la pila 
    // para volver automáticamente al menú principal.
    historialPantallas->desapilar(); 
}

void GestionPantallas::MenuReservaVuelo() {
    DibujarHeader("Inicio > Reservar > Vuelo");
    int indiceVuelo, equipaje, cabina, asiento, clase;
    string origen, destino;

    ColorUI::printGradient("=== COMPRA DE TICKETS ===\n", Paletas::TemaPrincipal, false);

    // ... (Mantén tu código actual de obtener orígenes) ...
    
    cout << "\n\n> Ingrese opcion (0 para cancelar): ";
    int selO = LeerOpcion();
    if (selO <= 0 /* || selO > origenes.size() */) {
        historialPantallas->desapilar(); // El usuario canceló, retrocedemos.
        return; 
    }
    
    // ... (El resto de tu lógica de reserva de vuelos) ...
    
    // Al final del proceso de compra exitoso:
    LimpiarConsola();
    ColorUI::printGradient("TICKET COMPRADO CON EXITO", gege, false);
    pausarConsola();
    
    // Retrocedemos al menú de reservas automáticamente
    historialPantallas->desapilar(); 
}
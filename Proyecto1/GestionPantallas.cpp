#include "GestionPantallas.h"
#include <iomanip>

GestionPantallas::GestionPantallas(ControladorPrincipal* ptrPrincipal, Usuario* ptrUsuario) {
    principal = ptrPrincipal;
    userActual = ptrUsuario;
    historialPantallas = new Pila<PantallaID>(); 
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
// MOTOR CENTRAL DE PANTALLAS
// ====================================================================
void GestionPantallas::IniciarMotorNavegacion() {
    historialPantallas->apilar(PANTALLA_PRINCIPAL);

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
// MENUS PRINCIPALES
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
        case '7': LimpiarConsola(); creditos(); break; 
        case '0':
            LimpiarConsola();
            ColorUI::printGradient("Cerrando sesion...", Alerta, false);
            LimpiarConsola();
            historialPantallas->desapilar();
            break;
        default: break;
    }
}

void GestionPantallas::MenuCatalogos(){
    DibujarHeader("Inicio > Catalogo de Servicios");
    ColorUI::printGradient("\n================CATALOGO DE SERVICIOS==============", Exito, false);
    ColorUI::printGradient("\n[1] CATALOGO VUELOS DISPONIBLES", Exito, false);
    ColorUI::printGradient("\n[2] CATALOGO DE HOTELES DISPONIBLES", Exito, false);
    ColorUI::printGradient("\n[3] CATALOGO DE PAQUETES DISPONIBLES", Exito, false);
    ColorUI::printGradient("\n[0] SALIR", Exito, false);
    
    char opcion = _getch();
    switch (opcion) {
        case '1': historialPantallas->apilar(PANTALLA_FILTROS_VUELOS); break;
        case '2': historialPantallas->apilar(PANTALLA_FILTROS_HOTELES); break;
        case '3': historialPantallas->apilar(PANTALLA_FILTROS_PAQUETES); break;
        case '0': historialPantallas->desapilar(); break;
    }
}

void GestionPantallas::MenuReservas() {
    DibujarHeader("Inicio > Reservar un Servicio");
    ColorUI::printGradient("\n================RESERVAR UN SERVICIO==============", Exito, false);
    ColorUI::printGradient("\n[1] RESERVAR TICKET DE VUELO", Exito, false);
    ColorUI::printGradient("\n[2] RESERVAR TICKET DE HOTEL", Exito, false);
    ColorUI::printGradient("\n[3] RESERVAR TICKET DE PAQUETE", Exito, false);
    ColorUI::printGradient("\n[0] SALIR", Exito, false);
    
    char opcion = _getch();
    switch (opcion) {
        case '1': historialPantallas->apilar(PANTALLA_RESERVA_VUELO); break;
        case '2': historialPantallas->apilar(PANTALLA_RESERVA_HOTEL); break;
        case '3': historialPantallas->apilar(PANTALLA_RESERVA_PAQUETE); break;
        case '0': historialPantallas->desapilar(); break;
    }
}

// ====================================================================
// SUBMENUS DE FILTROS
// ====================================================================
void GestionPantallas::MenuFiltrosReservas() {
    DibujarHeader("Inicio > Mi Historial de Reservas");
    ColorUI::printGradient("\n================MENU HISTORIAL==============", Paletas::Exito, false);
    ColorUI::printGradient("\n[1] FILTRAR MIS RESERVAS POR SERVICIO", Paletas::Exito, false);
    ColorUI::printGradient("\n[2] MOSTRAR TODAS MIS RESERVAS", Paletas::Exito, false);
    ColorUI::printGradient("\n[0] SALIR", Paletas::Exito, false);
    
    char opcion = _getch();
    switch (opcion) {
        case '1': {
            DibujarHeader("Inicio > Mi Historial de Reservas > Filtrar");
            ColorUI::printGradient("\n================ SELECCIONE TIPO ================\n", Paletas::TemaPrincipal, false);
            cout << " [1] Vuelos\n";
            cout << " [2] Hoteles\n";
            cout << " [3] Paquetes\n";
            cout << "\n> Ingrese opcion (0 para cancelar): ";
            int sel = LeerOpcion();
            string reserva = "";
            if (sel == 1) reserva = "VUELO";
            else if (sel == 2) reserva = "HOTEL";
            else if (sel == 3) reserva = "PAQUETE";
            
            if (reserva != "") {
                DibujarHeader("Inicio > Mi Historial de Reservas > Filtrar");
                ColorUI::printGradient("Mostrando tus reservas de tipo: " + reserva + "\n", Paletas::Exito, false);
                principal->FiltrarReservasPorTipoUsuario(reserva, userActual->getCodigo());
            }
            pausarConsola();
            break;
        }
        case '2': {
            DibujarHeader("Inicio > Mi Historial de Reservas > Todas");
            principal->FiltrarReservasPorUsuario(userActual->getCodigo());
            pausarConsola();
            break;
        }
        case '0': historialPantallas->desapilar(); break;
    }
}

void GestionPantallas::MenuFiltrosVuelos() {
    DibujarHeader("Inicio > Catalogo > Vuelos");
    ColorUI::printGradient("\n================FILTROS VUELOS==============", Exito, false);
    ColorUI::printGradient("\n[1] VUELOS POR ORIGEN", Exito, false);
    ColorUI::printGradient("\n[2] VUELOS POR DESTINO", Exito, false);
    ColorUI::printGradient("\n[3] VUELOS POR FECHA", Exito, false);
    ColorUI::printGradient("\n[4] VUELOS POR PRESUPUESTO", Exito, false);
    ColorUI::printGradient("\n[5] VUELOS POR PRECIO (MAYOR A MENOR)", Exito, false);
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
        case '2': {
            DibujarHeader("Inicio > Catalogo > Vuelos > Por Destino");
            vector<string> destinos;
            Lista<Vuelo*>* vuelos = principal->getControladorVuelos()->getVuelos();
            for(int i=0; i<vuelos->longitud(); i++){
                string o = vuelos->obtenerPos(i)->getDestino();
                bool existe = false;
                for(string& org : destinos) { if(org == o) existe = true; }
                if(!existe) destinos.push_back(o);
            }
            if (destinos.empty()) { ColorUI::Alertas::MostrarInfo("No hay vuelos disponibles."); pausarConsola(); break; }
            ColorUI::printGradient("\n================ SELECCIONE DESTINO ================\n", Paletas::TemaPrincipal, false);
            for(size_t i=0; i<destinos.size(); i++) {
                cout << " [" << i+1 << "] " << left << setw(20) << destinos[i];
                if((i+1)%3==0) cout << "\n";
            }
            cout << "\n\n> Ingrese opcion: ";
            int sel = LeerOpcion();
            if (sel > 0 && sel <= destinos.size()) {
                principal->FiltrarVuelosPorDestino(destinos[sel-1]);
            } else {
                ColorUI::Alertas::MostrarError("Opcion invalida.");
            }
            pausarConsola();
            break;
        }
        case '3': {
            DibujarHeader("Inicio > Catalogo > Vuelos > Por Fecha");
            vector<string> fechas;
            Lista<Vuelo*>* vuelos = principal->getControladorVuelos()->getVuelos();
            for(int i=0; i<vuelos->longitud(); i++){
                string f = vuelos->obtenerPos(i)->getFecha();
                bool existe = false;
                for(string& org : fechas) { if(org == f) existe = true; }
                if(!existe) fechas.push_back(f);
            }
            if (fechas.empty()) { ColorUI::Alertas::MostrarInfo("No hay vuelos disponibles."); pausarConsola(); break; }
            ColorUI::printGradient("\n================ SELECCIONE FECHA ================\n", Paletas::TemaPrincipal, false);
            for(size_t i=0; i<fechas.size(); i++) {
                cout << " [" << i+1 << "] " << left << setw(20) << fechas[i];
                if((i+1)%3==0) cout << "\n";
            }
            cout << "\n\n> Ingrese opcion: ";
            int sel = LeerOpcion();
            if (sel > 0 && sel <= fechas.size()) {
                principal->FiltrarVuelosPorFecha(fechas[sel-1]);
            } else {
                ColorUI::Alertas::MostrarError("Opcion invalida.");
            }
            pausarConsola();
            break;
        }
        case '4': {
            float presupuesto;
            ColorUI::printGradient("\nDIGITE EL PRESUPUESTO\n", Exito, false); cin >> presupuesto; cin.ignore();
            principal->FiltrarVuelosPorPresupuesto(presupuesto);
            pausarConsola();
            break;
        }
        case '5': {
            principal->FiltrarVuelosDeMayorAMenorPrecio();
            pausarConsola();
            break;
        }
        case '6': {
            principal->MostrarVuelos();
            break;
        }
        case '0': historialPantallas->desapilar(); break;
    }
}

void GestionPantallas::MenuFiltrosPaquetes() {
    DibujarHeader("Inicio > Catalogo > Paquetes");
    ColorUI::printGradient("\n================FILTROS PAQUETES==============", Exito, false);
    ColorUI::printGradient("\n[1] PAQUETES POR ORIGEN", Exito, false);
    ColorUI::printGradient("\n[2] PAQUETES POR DESTINO", Exito, false);
    ColorUI::printGradient("\n[3] PAQUETES POR PRECIO (MAYOR A MENOR)", Exito, false);
    ColorUI::printGradient("\n[4] PAQUETES POR PRESUPUESTO", Exito, false);
    ColorUI::printGradient("\n[5] VER TODOS LOS PAQUETES", Exito, false);
    ColorUI::printGradient("\n[0] SALIR", Exito, false);
    
    char opcion = _getch();
    switch (opcion) {
        case '1': {
            DibujarHeader("Inicio > Catalogo > Paquetes > Por Origen");
            vector<string> origenes;
            Lista<Paquete*>* paquetes = principal->getControladorPaquetes()->getPaquetes();
            for(int i=0; i<paquetes->longitud(); i++){
                string o = paquetes->obtenerPos(i)->getVueloIncluido()->getOrigen();
                bool existe = false;
                for(string& org : origenes) { if(org == o) existe = true; }
                if(!existe) origenes.push_back(o);
            }
            if (origenes.empty()) { ColorUI::Alertas::MostrarInfo("No hay paquetes disponibles."); pausarConsola(); break; }
            ColorUI::printGradient("\n================ SELECCIONE ORIGEN ================\n", Paletas::TemaPrincipal, false);
            for(size_t i=0; i<origenes.size(); i++) {
                cout << " [" << i+1 << "] " << left << setw(20) << origenes[i];
                if((i+1)%3==0) cout << "\n";
            }
            cout << "\n\n> Ingrese opcion: ";
            int sel = LeerOpcion();
            if (sel > 0 && sel <= origenes.size()) {
                principal->FiltrarPaquetesPorOrigen(origenes[sel-1]);
            } else {
                ColorUI::Alertas::MostrarError("Opcion invalida.");
            }
            pausarConsola();
            break;
        }
        case '2': {
            DibujarHeader("Inicio > Catalogo > Paquetes > Por Destino");
            vector<string> destinos;
            Lista<Paquete*>* paquetes = principal->getControladorPaquetes()->getPaquetes();
            for(int i=0; i<paquetes->longitud(); i++){
                string o = paquetes->obtenerPos(i)->getVueloIncluido()->getDestino();
                bool existe = false;
                for(string& org : destinos) { if(org == o) existe = true; }
                if(!existe) destinos.push_back(o);
            }
            if (destinos.empty()) { ColorUI::Alertas::MostrarInfo("No hay paquetes disponibles."); pausarConsola(); break; }
            ColorUI::printGradient("\n================ SELECCIONE DESTINO ================\n", Paletas::TemaPrincipal, false);
            for(size_t i=0; i<destinos.size(); i++) {
                cout << " [" << i+1 << "] " << left << setw(20) << destinos[i];
                if((i+1)%3==0) cout << "\n";
            }
            cout << "\n\n> Ingrese opcion: ";
            int sel = LeerOpcion();
            if (sel > 0 && sel <= destinos.size()) {
                principal->FiltrarPaquetesPorDestino(destinos[sel-1]);
            } else {
                ColorUI::Alertas::MostrarError("Opcion invalida.");
            }
            pausarConsola();
            break;
        }
        case '3': {
            LimpiarConsola();
            principal->FiltrarPaquetesDeMayorAMenorPrecio();
            pausarConsola();
            break;
        }
        case '4': {
            LimpiarConsola();
            float presupuesto;
            ColorUI::printGradient("\nDIGITE EL PRESUPUESTO", Exito, false); cin >> presupuesto; cin.ignore();
            principal->FiltrarPaquetesPorPresupuesto(presupuesto);
            pausarConsola();
            break;
        }
        case '5': {
            principal->MostrarPaquetes();
            break;
        }
        case '0': historialPantallas->desapilar(); break;
    }
}

void GestionPantallas::MenuFiltrosHoteles() {
    DibujarHeader("Inicio > Catalogo > Hoteles");
    ColorUI::printGradient("\n================FILTROS HOTELES==============", Exito, false);
    ColorUI::printGradient("\n[1] HOTELES POR CIUDAD", Exito, false);
    ColorUI::printGradient("\n[2] HOTELES POR CALIFICACION (MAYOR A MENOR)", Exito, false);
    ColorUI::printGradient("\n[3] HOTELES POR PRECIO NOCHE (MAYOR A MENOR)", Exito, false);
    ColorUI::printGradient("\n[4] HOTELES POR PRESUPUESTO", Exito, false);
    ColorUI::printGradient("\n[5] CALIFICAR UN HOTEL", Exito, false);
    ColorUI::printGradient("\n[6] VER TODOS LOS HOTELES", Exito, false);
    ColorUI::printGradient("\n[0] SALIR", Exito, false);
    
    char opcion = _getch();
    switch (opcion) {
        case '1': {
            DibujarHeader("Inicio > Catalogo > Hoteles > Por Ciudad");
            vector<string> ciudades;
            Lista<Hotel*>* hoteles = principal->getControladorHoteles()->getHoteles();
            for(int i=0; i<hoteles->longitud(); i++){
                string c = hoteles->obtenerPos(i)->getCiudad();
                bool existe = false;
                for(string& org : ciudades) { if(org == c) existe = true; }
                if(!existe) ciudades.push_back(c);
            }
            if (ciudades.empty()) { ColorUI::Alertas::MostrarInfo("No hay hoteles disponibles."); pausarConsola(); break; }
            ColorUI::printGradient("\n================ SELECCIONE CIUDAD ================\n", Paletas::TemaPrincipal, false);
            for(size_t i=0; i<ciudades.size(); i++) {
                cout << " [" << i+1 << "] " << left << setw(20) << ciudades[i];
                if((i+1)%3==0) cout << "\n";
            }
            cout << "\n\n> Ingrese opcion: ";
            int sel = LeerOpcion();
            if (sel > 0 && sel <= ciudades.size()) {
                principal->FiltrarHotelesPorCiudad(ciudades[sel-1]);
            } else {
                ColorUI::Alertas::MostrarError("Opcion invalida.");
            }
            pausarConsola();
            break;
        }
        case '2': {
            LimpiarConsola();
            principal->FiltrarHotelesPorMayorCalificacion();
            pausarConsola();
            break;
        }
        case '3': {
            LimpiarConsola();
            principal->FiltrarHotelesDeMayorAMenorPrecio();
            pausarConsola();
            break;
        }
        case '4': {
            LimpiarConsola();
            float presupuesto;
            ColorUI::printGradient("\nDIGITE EL PRESUPUESTO", Exito, false); cin >> presupuesto; cin.ignore();
            principal->FiltrarHotelesPorPresupuesto(presupuesto);
            pausarConsola();
            break;
        }
        case '5': {
            historialPantallas->apilar(PANTALLA_CALIFICAR_HOTEL);
            break;
        }
        case '6': {
            principal->MostrarHoteles();
            break;
        }
        case '0': historialPantallas->desapilar(); break;
    }
}

// ====================================================================
// PANTALLAS DE ACCIONES LINEALES (Se cierran solas al final)
// ====================================================================

void GestionPantallas::HistorialReservas() {
    ColorUI::printGradient("=== MI HISTORIAL DE RESERVAS ===", TemaPrincipal, false);
    historialPantallas->apilar(PANTALLA_FILTROS_RESERVAS);
    // Removemos esta del historial para que al volver de filtros, vaya al principal
    historialPantallas->desapilar(); 
}

void GestionPantallas::MenuDatosUsuario(){
    DibujarHeader("Inicio > Mis Datos");
    ColorUI::printGradient("\n\t\t\t\t\tDATOS DEL USUARIO ACTUAL\n", Exito, false);
    principal->FiltrarUsuarioPorCodigo(userActual->getCodigo()); 
    pausarConsola();
    historialPantallas->desapilar();
}

void GestionPantallas::MenuCancelarReserva() {
    DibujarHeader("Inicio > Cancelar Reserva");
    int id;
    principal->FiltrarReservasPorUsuario(userActual->getCodigo());
    if (!principal->VerificarReservas(userActual->getCodigo())) {
        cout << "No hay reservas registradas a su nombre" << endl;
        pausarConsola();
        historialPantallas->desapilar();
        return;
    }
    
    ColorUI::printGradient("\nDIGITE EL ID DE LA RESERVA A ELIMINAR\n", Exito, false);
    cin >> id;
    cin.ignore();
    
    if (principal->CancelarReservaUsuario(userActual->getCodigo(), id)) {
        ColorUI::printGradient("\nEL MONTO SE REEMBOLSARA EN SU CUENTA MAXIMO 10 DIAS HABILES", Exito, false);
    } else {
        ColorUI::printGradient("\nError al cancelar la reserva.", Alerta, false);
    }
    
    pausarConsola();
    historialPantallas->desapilar();
}

void GestionPantallas::MenuCalificacionHotel() {
    DibujarHeader("Inicio > Calificar Hotel");
    string ciudad, nombre;
    float calificaion;
    int id;

    vector<string> ciudades;
    Lista<Hotel*>* hoteles = principal->getControladorHoteles()->getHoteles();
    for(int i=0; i<hoteles->longitud(); i++){
        string c = hoteles->obtenerPos(i)->getCiudad();
        bool existe = false;
        for(string& org : ciudades) { if(org == c) existe = true; }
        if(!existe) ciudades.push_back(c);
    }
    if (ciudades.empty()) { 
        ColorUI::Alertas::MostrarInfo("No hay hoteles disponibles."); 
        pausarConsola(); 
        historialPantallas->desapilar();
        return; 
    }
    ColorUI::printGradient("\n================ SELECCIONE CIUDAD ================\n", Paletas::TemaPrincipal, false);
    for(size_t i=0; i<ciudades.size(); i++) {
        cout << " [" << i+1 << "] " << left << setw(20) << ciudades[i];
        if((i+1)%3==0) cout << "\n";
    }
    cout << "\n\n> Ingrese opcion (0 para cancelar): ";
    int selC = LeerOpcion();
    if (selC <= 0 || selC > ciudades.size()) {
        historialPantallas->desapilar();
        return;
    }
    ciudad = ciudades[selC-1];

    DibujarHeader("Inicio > Calificar Hotel");
    ColorUI::printGradient("Ciudad seleccionada: " + ciudad + "\n", Paletas::Exito, false);

    principal->FiltrarHotelesPorCiudad(ciudad);
    
    ColorUI::printGradient("\nIngresa el ID del hotel que deseas calificar (o -1 para salir): ", Paletas::Exito, false, false);
    id = LeerOpcion();
    if (id < 0 || id >= hoteles->longitud()) {
        historialPantallas->desapilar();
        return;
    }
    
    nombre = hoteles->obtenerPos(id)->getNombre();

    ColorUI::printGradient("\nDIGITE LA CALIFICACION (1.0 - 5.0): ", Paletas::Exito, false, false);
    cin >> calificaion; cin.ignore();
    
    principal->CalificarHotel(nombre, calificaion);
    pausarConsola();
    historialPantallas->desapilar();
}

void GestionPantallas::MenuReservaVuelo() {
    DibujarHeader("Inicio > Reservar > Vuelo");
    int indiceVuelo, equipaje, cabina, asiento, clase;
    string origen, destino, nombre;

    ColorUI::printGradient("=== COMPRA DE TICKETS ===\n", Paletas::TemaPrincipal, false);

    vector<string> origenes;
    Lista<Vuelo*>* vuelos = principal->getControladorVuelos()->getVuelos();
    for(int i=0; i<vuelos->longitud(); i++){
        string o = vuelos->obtenerPos(i)->getOrigen();
        bool existe = false;
        for(string& org : origenes) { if(org == o) existe = true; }
        if(!existe) origenes.push_back(o);
    }
    if (origenes.empty()) { 
        ColorUI::Alertas::MostrarInfo("No hay vuelos disponibles."); 
        pausarConsola(); 
        historialPantallas->desapilar();
        return; 
    }
    ColorUI::printGradient("\n================ SELECCIONE ORIGEN ================\n", Paletas::TemaPrincipal, false);
    for(size_t i=0; i<origenes.size(); i++) {
        cout << " [" << i+1 << "] " << left << setw(20) << origenes[i];
        if((i+1)%3==0) cout << "\n";
    }
    cout << "\n\n> Ingrese opcion (0 para cancelar): ";
    int selO = LeerOpcion();
    if (selO <= 0 || selO > origenes.size()) {
        historialPantallas->desapilar();
        return;
    }
    origen = origenes[selO-1];

    DibujarHeader("Inicio > Reservar > Vuelo");
    ColorUI::printGradient("Origen seleccionado: " + origen + "\n", Paletas::Exito, false);

    vector<string> destinos;
    for(int i=0; i<vuelos->longitud(); i++){
        if (vuelos->obtenerPos(i)->getOrigen() == origen) {
            string d = vuelos->obtenerPos(i)->getDestino();
            bool existe = false;
            for(string& des : destinos) { if(des == d) existe = true; }
            if(!existe) destinos.push_back(d);
        }
    }
    if (destinos.empty()) { 
        ColorUI::Alertas::MostrarInfo("No hay destinos desde este origen."); 
        pausarConsola(); 
        historialPantallas->desapilar();
        return; 
    }
    ColorUI::printGradient("\n================ SELECCIONE DESTINO ================\n", Paletas::TemaPrincipal, false);
    for(size_t i=0; i<destinos.size(); i++) {
        cout << " [" << i+1 << "] " << left << setw(20) << destinos[i];
        if((i+1)%3==0) cout << "\n";
    }
    cout << "\n\n> Ingrese opcion (0 para cancelar): ";
    int selD = LeerOpcion();
    if (selD <= 0 || selD > destinos.size()) {
        historialPantallas->desapilar();
        return;
    }
    destino = destinos[selD-1];

    cout << "\n";
    if (!principal->ConsultarVuelos(origen, destino)) {
        pausarConsola();
        historialPantallas->desapilar();
        return;
    }

    ColorUI::printGradient("================================", Paletas::Tux, false);
    ColorUI::printGradient("\nIngresa el ID del vuelo que deseas reservar (o -1 para salir): ", Paletas::Exito, false, false);
    indiceVuelo = LeerOpcion();

    if (indiceVuelo == -1) {
        historialPantallas->desapilar();
        return;
    }

    if (indiceVuelo < 0 || indiceVuelo >= principal->getControladorVuelos()->getVuelos()->longitud()) {
        ColorUI::printGradient("ID de vuelo invalido. Abortando compra...", Alerta, false);
        pausarConsola();
        historialPantallas->desapilar();
        return;
    }

    LimpiarConsola();
    ColorUI::printGradient("=== SELECCION DE ASIENTO ===", TemaPrincipal, false);
    cout << "\n\tMAPA DE ASIENTOS DEL VUELO\n\n";
    for (int i = 1; i <= 30; i++) {
        bool disponible = principal->VerificarAsiento(i, indiceVuelo);
        string textoAsiento = "[";
        if (i < 10) textoAsiento += "0";
        textoAsiento += to_string(i) + "]";

        if (disponible) {
            ColorUI::printGradient(textoAsiento, Exito, false, false); 
        }
        else {
            ColorUI::printGradient("[XX]", Alerta, false, false); 
        }

        if (i % 6 == 0) cout << "\n\n"; 
        else if (i % 3 == 0) ColorUI::printGradient("   ||   ", TemaPrincipal, false, false); 
        else cout << " "; 
    }

    bool asientoValido = false;
    while (!asientoValido) {
        ColorUI::printGradient("\n\nIngresa el numero del asiento que deseas (1-30): ", Exito, false, false);
        asiento = LeerOpcion();
        if (principal->VerificarAsiento(asiento, indiceVuelo)) {
            asientoValido = true;
        }
        else {
            ColorUI::printGradient("El asiento seleccionado no existe o ya esta ocupado.", Alerta, false);
        }
    }

    LimpiarConsola();

    cout << endl;
    ColorUI::printGradient("Ingresa la cantidad de equipaje en bodega: ", Exito, false, false);
    equipaje = LeerOpcion();

    cout << endl;
    ColorUI::printGradient("Ingresa la cantidad de equipaje en cabina: ", Exito, false, false);
    cabina = LeerOpcion();

    cout << endl;
    ColorUI::printGradient("Ingresa que clase deseas adquirir (1-ECONOMICA, 2-PREMIUM, 3-EJECUTIVA, 4-PRIMERA): ", Exito, false, false);
    clase = LeerOpcion();
    
    char opcion;
    ColorUI::printGradient("\nESTA SEGURO QUE DESEA CONTINUAR CON LA COMPRA? (1-SI, 2-NO): ", Exito, false, false);
    opcion = _getch();

    if (opcion == '2' || opcion != '1') {
        cout << "\n";
        ColorUI::printGradient("OPERACION CANCELADA", Exito, false);
        pausarConsola();
        historialPantallas->desapilar();
        return; 
    }
    
    principal->ComprarTicket(indiceVuelo, userActual, equipaje, cabina, asiento, clase);

    LimpiarConsola();
    ColorUI::printGradient("TICKET COMPRADO CON EXITO", gege, false);
    pausarConsola();
    ColorUI::printGradient("El asiento [" + to_string(asiento) + "] ha sido reservado para " + userActual->getNombre(), Exito, false);
    cout << "\n";
    pausarConsola();
    historialPantallas->desapilar();
}

void GestionPantallas::MenuReservaHotel() {
    string ciudad,fechaIngreso;
    int idHotel, noches, habitacion, tipoO, tipoC, tipoS;

    DibujarHeader("Inicio > Reservar > Hotel");
    ColorUI::printGradient("=== RESERVA DE HOTELES ===\n", TemaPrincipal, false);
    
    vector<string> ciudades;
    Lista<Hotel*>* hoteles = principal->getControladorHoteles()->getHoteles();
    for(int i=0; i<hoteles->longitud(); i++){
        string c = hoteles->obtenerPos(i)->getCiudad();
        bool existe = false;
        for(string& org : ciudades) { if(org == c) existe = true; }
        if(!existe) ciudades.push_back(c);
    }
    if (ciudades.empty()) { 
        ColorUI::Alertas::MostrarInfo("No hay hoteles disponibles."); 
        pausarConsola(); 
        historialPantallas->desapilar();
        return; 
    }
    ColorUI::printGradient("\n================ SELECCIONE CIUDAD ================\n", Paletas::TemaPrincipal, false);
    for(size_t i=0; i<ciudades.size(); i++) {
        cout << " [" << i+1 << "] " << left << setw(20) << ciudades[i];
        if((i+1)%3==0) cout << "\n";
    }
    cout << "\n\n> Ingrese opcion (0 para cancelar): ";
    int selC = LeerOpcion();
    if (selC <= 0 || selC > ciudades.size()) {
        historialPantallas->desapilar();
        return;
    }
    ciudad = ciudades[selC-1];

    DibujarHeader("Inicio > Reservar > Hotel");
    ColorUI::printGradient("Ciudad seleccionada: " + ciudad + "\n", Paletas::Exito, false);

    principal->FiltrarHotelesPorCiudad(ciudad);
    if (!principal->VerificarHoteles(ciudad)) {
        cout << "No hay hoteles disponibles" << endl;
        pausarConsola();
        historialPantallas->desapilar();
        return;
    }
    ColorUI::printGradient("\n================================", Tux, false);
    ColorUI::printGradient("\nIngresa el ID del hotel que deseas reservar (o -1 para salir): ", Exito, false, false);
    idHotel = LeerOpcion();
    if (idHotel == -1) {
        historialPantallas->desapilar();
        return;
    }

    if (idHotel < 0 || idHotel >= principal->getControladorHoteles()->getHoteles()->longitud()) {
        ColorUI::printGradient("ID de hotel invalido.", Alerta, false);
        pausarConsola();
        historialPantallas->desapilar();
        return;
    }

    LimpiarConsola();
    cout << "\n\tMAPA DE HABITACIONES DEL HOTEL\n\n";

    for (int i = 1; i <= 30; i++) {
        bool disponible = principal->VerificarHabitacion(i, idHotel);

        string textoHab = "[";
        if (i < 10) textoHab += "0";
        textoHab += to_string(i) + "]";

        if (disponible) ColorUI::printGradient(textoHab, Register, false, false); 
        else ColorUI::printGradient("[XX]", Alerta, false, false); 

        if (i % 5 == 0) cout << "\n\n";
        else cout << "   ";
    }

    ColorUI::printGradient("\n\nNumero de habitacion deseada: ", Exito, false, false);
    habitacion = LeerOpcion();
    ColorUI::printGradient("Cantidad de noches: ", Exito, false, false);
    noches = LeerOpcion();
    ColorUI::printGradient("Fecha de Ingreso (DD-MM-AAAA): ", Exito, false, false);
    cin >> fechaIngreso; cin.ignore();
    ColorUI::printGradient("TIPO DE HABITACION (1-INDIVIDUAL,2-SUITE,3-PRESIDENCIAL): ", Exito, false, false);
    cin >> tipoO; cin.ignore();
    ColorUI::printGradient("TIPO DE CAMA (1-INDIVIDUAL,2-MATRIMONIAL,3-QUEEN): ", Exito, false, false);
    cin >> tipoC; cin.ignore();
    ColorUI::printGradient("SERVICIOS (1-BASICO,2-PREMIUM,3-VIP): ", Exito, false, false);
    cin >> tipoS; cin.ignore();

    char opcion;
    ColorUI::printGradient("\nESTA SEGURO QUE DESEA CONTINUAR CON LA COMPRA? (1-SI, 2-NO): ", Exito, false, false);
    opcion = _getch();

    if (opcion == '2' || opcion != '1') {
        cout << "\n";
        ColorUI::printGradient("OPERACION CANCELADA", Exito, false);
        pausarConsola();
        historialPantallas->desapilar();
        return;
    }
    
    principal->ReservarHotel(idHotel, userActual, fechaIngreso,noches, habitacion, tipoO, tipoC, tipoS);

    LimpiarConsola();
    ColorUI::printGradient("RESERVA DE HOTEL COMPLETADA", gege, false);
    cout << "\n";
    pausarConsola();
    historialPantallas->desapilar();
}

void GestionPantallas::MenuReservaPaquete() {
    string ciudad;
    int idPaquete, noches, equipajeIda, equipajeRetorno, asiento, clase;

    DibujarHeader("Inicio > Reservar > Paquete Turistico");
    ColorUI::printGradient("=== RESERVA DE PAQUETES TURISTICOS ===\n", TemaPrincipal, false);
    
    vector<string> destinos;
    Lista<Paquete*>* paquetes = principal->getControladorPaquetes()->getPaquetes();
    for(int i=0; i<paquetes->longitud(); i++){
        string o = paquetes->obtenerPos(i)->getVueloIncluido()->getDestino();
        bool existe = false;
        for(string& org : destinos) { if(org == o) existe = true; }
        if(!existe) destinos.push_back(o);
    }
    if (destinos.empty()) { 
        ColorUI::Alertas::MostrarInfo("No hay paquetes disponibles."); 
        pausarConsola(); 
        historialPantallas->desapilar();
        return; 
    }
    ColorUI::printGradient("\n================ SELECCIONE DESTINO ================\n", Paletas::TemaPrincipal, false);
    for(size_t i=0; i<destinos.size(); i++) {
        cout << " [" << i+1 << "] " << left << setw(20) << destinos[i];
        if((i+1)%3==0) cout << "\n";
    }
    cout << "\n\n> Ingrese opcion (0 para cancelar): ";
    int selD = LeerOpcion();
    if (selD <= 0 || selD > destinos.size()) {
        historialPantallas->desapilar();
        return;
    }
    ciudad = destinos[selD-1];

    DibujarHeader("Inicio > Reservar > Paquete Turistico");
    ColorUI::printGradient("Destino seleccionado: " + ciudad + "\n", Paletas::Exito, false);

    principal->FiltrarPaquetesPorDestino(ciudad);
    if (!principal->VerificarPaquetes(ciudad)) {
        cout << "No hay paquetes disponibles" << endl;
        pausarConsola();
        historialPantallas->desapilar();
        return;
    }
    ColorUI::printGradient("\n================================", Tux, false);
    ColorUI::printGradient("\nIngresa el ID del paquete que deseas comprar (o -1 para salir): ", Exito, false, false);
    idPaquete = LeerOpcion();
    if (idPaquete == -1) {
        historialPantallas->desapilar();
        return;
    }

    if (idPaquete < 0 || idPaquete >= principal->getControladorPaquetes()->getPaquetes()->longitud()) {
        ColorUI::printGradient("ID de paquete invalido. Abortando compra...", Alerta, false);
        pausarConsola();
        historialPantallas->desapilar();
        return;
    }

    ColorUI::printGradient("Cantidad de noches de estadia en hotel incluido: ", Exito, false, false);
    noches = LeerOpcion();
    ColorUI::printGradient("Cantidad de equipaje para la IDA: ", Exito, false, false);
    equipajeIda = LeerOpcion();
    ColorUI::printGradient("Cantidad de equipaje para el RETORNO: ", Exito, false, false);
    equipajeRetorno = LeerOpcion();
    ColorUI::printGradient("Numero de asiento preferido en vuelo IDA y RETORNO: ", Exito, false, false);
    asiento = LeerOpcion();
    ColorUI::printGradient("DIGITE LA CLASE: ", Exito, false, false);
    clase = LeerOpcion();
    
    char opcion;
    ColorUI::printGradient("\nESTA SEGURO QUE DESEA CONTINUAR CON LA COMPRA? (1-SI, 2-NO): ", Exito, false, false);
    opcion = _getch();

    if (opcion == '2' || opcion != '1') {
        cout << "\n";
        ColorUI::printGradient("OPERACION CANCELADA", Exito, false);
        pausarConsola();
        historialPantallas->desapilar();
        return;
    }
    
    principal->ReservarPaquete(idPaquete, userActual, noches, equipajeIda, equipajeRetorno, clase, asiento);

    LimpiarConsola();
    ColorUI::printGradient("PAQUETE COMPRADO CON EXITO", gege, false);
    cout << "\n";
    pausarConsola();
    historialPantallas->desapilar();
}
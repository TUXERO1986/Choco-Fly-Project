#include "GestionPantallas.h"
#include "AnimacionConsola.h"
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

void GestionPantallas::Menuprincipal() {
    char opcion = AnimacionConsola::AnimarMenuPrincipal();

    switch (opcion) {
        case '1': AnimacionConsola::TransicionAvion(); historialPantallas->apilar(PANTALLA_CATALOGOS); break;
        case '2': AnimacionConsola::TransicionAvion(); historialPantallas->apilar(PANTALLA_RESERVAS); break;
        case '3': AnimacionConsola::TransicionAvion(); historialPantallas->apilar(PANTALLA_DATOS_USUARIO); break;
        case '4': AnimacionConsola::TransicionAvion(); historialPantallas->apilar(PANTALLA_HISTORIAL_RESERVAS); break;
        case '5': AnimacionConsola::TransicionAvion(); historialPantallas->apilar(PANTALLA_CANCELAR_RESERVA); break;
        case '6': AnimacionConsola::TransicionAvion(); historialPantallas->apilar(PANTALLA_CALIFICAR_HOTEL); break;
        case '7': LimpiarConsola(); creditos(); break; 
        case '0':
            LimpiarConsola();
            AnimacionConsola::AvionVolando(1500);
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
                
                principal->ConsultarCatalogoDinamico<Reserva>(
                    userActual->getReservas(), 
                    "MIS RESERVAS DE TIPO " + reserva, 
                    [reserva](Reserva* r){ return r->getTipoReserva() == reserva; }
                );
            }
            pausarConsola();
            break;
        }
        case '2': {
            DibujarHeader("Inicio > Mi Historial de Reservas > Todas");
            principal->ConsultarCatalogoDinamico<Reserva>(
                userActual->getReservas(), 
                "TODAS MIS RESERVAS", 
                [](Reserva* r){ return true; }
            );
            pausarConsola();
            break;
        }
        case '0': historialPantallas->desapilar(); break;
    }
}

void GestionPantallas::MenuFiltrosVuelos() {
    DibujarHeader("Inicio > Catalogo > Vuelos");
    ColorUI::printGradient("\n================FILTROS VUELOS==============", Paletas::Exito, false);
    ColorUI::printGradient("\n[1] VUELOS POR ORIGEN", Paletas::Exito, false);
    ColorUI::printGradient("\n[2] VUELOS POR DESTINO", Paletas::Exito, false);
    ColorUI::printGradient("\n[3] VUELOS POR FECHA", Paletas::Exito, false);
    ColorUI::printGradient("\n[4] VUELOS POR PRESUPUESTO", Paletas::Exito, false);
    ColorUI::printGradient("\n[5] VUELOS POR PRECIO (MAYOR A MENOR)", Paletas::Exito, false);
    ColorUI::printGradient("\n[6] VER TODOS LOS VUELOS", Paletas::Exito, false);
    ColorUI::printGradient("\n[0] SALIR", Paletas::Exito, false);
    
    char opcion = _getch();
    switch (opcion) {
    case '1': {
        DibujarHeader("Inicio > Catalogo > Vuelos > Por Origen");
        vector<string> origenes;
        Lista<Vuelo*>* vuelos = principal->getControladorVuelos()->getVuelos();
        for (int i = 0; i < vuelos->longitud(); i++) {
            string o = vuelos->obtenerPos(i)->getOrigen();
            bool existe = false;
            for (string& org : origenes) { if (org == o) existe = true; }
            if (!existe) origenes.push_back(o);
        }
        if (origenes.empty()) { ColorUI::Alertas::MostrarInfo("No hay vuelos disponibles."); pausarConsola(); break; }
        ColorUI::printGradient("\n================ SELECCIONE ORIGEN ================\n", Paletas::TemaPrincipal, false);
        for (size_t i = 0; i < origenes.size(); i++) {
            cout << " [" << i + 1 << "] " << left << setw(20) << origenes[i];
            if ((i + 1) % 3 == 0) cout << "\n";
        }
        cout << "\n\n> Ingrese opcion (0 para cancelar): ";
        int sel = LeerOpcion();
        if (sel <= 0) { break; }
        if (sel <= (int)origenes.size()) {
            string origen = origenes[sel - 1];
            principal->ConsultarCatalogoDinamico<Vuelo>(vuelos, "VUELOS DESDE: " + origen, [origen](Vuelo* v) {return v->getOrigen() == origen;});
        }
        else {
            ColorUI::Alertas::MostrarError("Opcion invalida.");
        }
        pausarConsola();
        break;
    }
    case '2': {
        DibujarHeader("Inicio > Catalogo > Vuelos > Por Destino");
        vector<string> destinos;
        Lista<Vuelo*>* vuelos = principal->getControladorVuelos()->getVuelos();
        for (int i = 0; i < vuelos->longitud(); i++) {
            string o = vuelos->obtenerPos(i)->getDestino();
            bool existe = false;
            for (string& org : destinos) { if (org == o) existe = true; }
            if (!existe) destinos.push_back(o);
        }
        if (destinos.empty()) { ColorUI::Alertas::MostrarInfo("No hay vuelos disponibles."); pausarConsola(); break; }
        ColorUI::printGradient("\n================ SELECCIONE DESTINO ================\n", Paletas::TemaPrincipal, false);
        for (size_t i = 0; i < destinos.size(); i++) {
            cout << " [" << i + 1 << "] " << left << setw(20) << destinos[i];
            if ((i + 1) % 3 == 0) cout << "\n";
        }
        cout << "\n\n> Ingrese opcion (0 para cancelar): ";
        int sel = LeerOpcion();
        if (sel <= 0) { break; }
        if (sel <= (int)destinos.size()) {
            Lista<Vuelo*>* temp = principal->getControladorVuelos()->getVuelos();
            string destino = destinos[sel - 1];
            principal->ConsultarCatalogoDinamico<Vuelo>(temp, "VUELOS A " + destino, [destino](Vuelo* v) {return v->getDestino() == destino;});
        }
        else {
            ColorUI::Alertas::MostrarError("Opcion invalida.");
        }
        pausarConsola();
        break;
    }
    case '3': {
        DibujarHeader("Inicio > Catalogo > Vuelos > Por Fecha");
        vector<string> fechas;
        Lista<Vuelo*>* vuelos = principal->getControladorVuelos()->getVuelos();
        for (int i = 0; i < vuelos->longitud(); i++) {
            string f = vuelos->obtenerPos(i)->getFecha();
            bool existe = false;
            for (string& org : fechas) { if (org == f) existe = true; }
            if (!existe) fechas.push_back(f);
        }
        if (fechas.empty()) { ColorUI::Alertas::MostrarInfo("No hay vuelos disponibles."); pausarConsola(); break; }
        ColorUI::printGradient("\n================ SELECCIONE FECHA ================\n", Paletas::TemaPrincipal, false);
        for (size_t i = 0; i < fechas.size(); i++) {
            cout << " [" << i + 1 << "] " << left << setw(20) << fechas[i];
            if ((i + 1) % 3 == 0) cout << "\n";
        }
        cout << "\n\n> Ingrese opcion (0 para cancelar): ";
        int sel = LeerOpcion();
        if (sel <= 0) { break; }
        if (sel <= (int)fechas.size()) {
            string fecha = fechas[sel - 1];
            principal->ConsultarCatalogoDinamico<Vuelo>(vuelos, "VUELOS EN LA FECHA: " + fecha, [fecha](Vuelo* v) {return v->getFecha() == fecha;});
        }
        else {
            ColorUI::Alertas::MostrarError("Opcion invalida.");
        }
        pausarConsola();
        break;
    }

        case '4': {
            DibujarHeader("Inicio > Catalogo > Vuelos > Por Presupuesto");
            float presupuesto;
            ColorUI::printGradient("\nDIGITE EL PRESUPUESTO: ", Paletas::Exito, false, false); 
            cin >> presupuesto; cin.ignore();
            
            principal->ConsultarCatalogoDinamico<Vuelo>(
                principal->getControladorVuelos()->getVuelos(),
                "VUELOS HASTA: $" + to_string(presupuesto),
                [presupuesto](Vuelo* v){ return v->getPrecioBase() <= presupuesto; }
            );
            pausarConsola();
            break;
        }
        case '5': {
            DibujarHeader("Inicio > Catalogo > Vuelos > Por Precio");
            Lista<Vuelo*>* aux= principal->getControladorVuelos()->getVuelos();
            aux->QuickSort([](Vuelo* v1,Vuelo* v2){return v1->getPrecioBase()<v2->getPrecioBase();});
            principal->ConsultarCatalogoDinamico<Vuelo>(aux,"VUELOS DE MENOR A MAYOR PRECIO",[](Vuelo* v){return true;});
            pausarConsola();
            break;
        }
        case '6': {
            DibujarHeader("Inicio > Catalogo > Vuelos > Todos");
            principal->ConsultarCatalogoDinamico<Vuelo>(
                principal->getControladorVuelos()->getVuelos(),
                "TODOS LOS VUELOS DISPONIBLES",
                [](Vuelo* v){ return true; } 
            );
            break;
        }
        case '0': historialPantallas->desapilar(); break;
    }
}

void GestionPantallas::MenuFiltrosHoteles() {
    DibujarHeader("Inicio > Catalogo > Hoteles");
    ColorUI::printGradient("\n================FILTROS HOTELES==============", Paletas::Exito, false);
    ColorUI::printGradient("\n[1] HOTELES POR CIUDAD", Paletas::Exito, false);
    ColorUI::printGradient("\n[2] HOTELES POR CALIFICACION (MAYOR A MENOR)", Paletas::Exito, false);
    ColorUI::printGradient("\n[3] HOTELES POR PRECIO NOCHE (MAYOR A MENOR)", Paletas::Exito, false);
    ColorUI::printGradient("\n[4] HOTELES POR PRESUPUESTO", Paletas::Exito, false);
    ColorUI::printGradient("\n[5] CALIFICAR UN HOTEL", Paletas::Exito, false);
    ColorUI::printGradient("\n[6] VER TODOS LOS HOTELES", Paletas::Exito, false);
    ColorUI::printGradient("\n[0] SALIR", Paletas::Exito, false);
    
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
            cout << "\n\n> Ingrese opcion (0 para cancelar): ";
            int sel = LeerOpcion();
            if (sel <= 0) { break; }
            if (sel <= (int)ciudades.size()) {
                string ciudad = ciudades[sel-1];
                principal->ConsultarCatalogoDinamico<Hotel>(
                    hoteles, 
                    "HOTELES EN: " + ciudad,
                    [ciudad](Hotel* h){ return h->getCiudad() == ciudad; }
                );
            } else {
                ColorUI::Alertas::MostrarError("Opcion invalida.");
            }
            pausarConsola();
            break;
        }
        case '2': {
            DibujarHeader("Inicio > Catalogo > Hoteles > Por Calificacion");
            Lista<Hotel*>* aux= principal->getControladorHoteles()->getHoteles();
            aux->QuickSort([](Hotel* h1,Hotel* h2){return h1->getPuntuacion()>h2->getPuntuacion();});
            principal->ConsultarCatalogoDinamico<Hotel>(aux,"HOTELES DE MAYOR A MENOR CALIFICACION",[](Hotel* h){return true;});
            pausarConsola();
            break;
        }
        case '3': {
            DibujarHeader("Inicio > Catalogo > Hoteles > Por Precio");
            Lista<Hotel*>* aux= principal->getControladorHoteles()->getHoteles();
            aux->QuickSort([](Hotel* h1,Hotel* h2){return h1->getPrecioBase()<h2->getPrecioBase();});
            principal->ConsultarCatalogoDinamico<Hotel>(aux,"HOTELES DE MENOR A MAYOR PRECIO", [](Hotel* h){return true;});
            pausarConsola();
            break;
        }
        case '4': {
            DibujarHeader("Inicio > Catalogo > Hoteles > Por Presupuesto");
            float presupuesto;
            ColorUI::printGradient("\nDIGITE EL PRESUPUESTO: ", Paletas::Exito, false, false); 
            cin >> presupuesto; cin.ignore();
            
            // Implementación dinámica
            principal->ConsultarCatalogoDinamico<Hotel>(
                principal->getControladorHoteles()->getHoteles(),
                "HOTELES HASTA: $" + to_string(presupuesto) + " POR NOCHE",
                [presupuesto](Hotel* h){ return h->getPrecioBase() <= presupuesto; }
            );
            pausarConsola();
            break;
        }
        case '5': {
            historialPantallas->apilar(PANTALLA_CALIFICAR_HOTEL);
            break;
        }
        case '6': {
            DibujarHeader("Inicio > Catalogo > Hoteles > Todos");
            principal->ConsultarCatalogoDinamico<Hotel>(
                principal->getControladorHoteles()->getHoteles(),
                "TODOS LOS HOTELES DISPONIBLES",
                [](Hotel* h){ return true; }
            );
            break;
        }
        case '0': historialPantallas->desapilar(); break;
    }
}

void GestionPantallas::MenuFiltrosPaquetes() {
    DibujarHeader("Inicio > Catalogo > Paquetes");
    ColorUI::printGradient("\n================FILTROS PAQUETES==============", Paletas::Exito, false);
    ColorUI::printGradient("\n[1] PAQUETES POR ORIGEN", Paletas::Exito, false);
    ColorUI::printGradient("\n[2] PAQUETES POR DESTINO", Paletas::Exito, false);
    ColorUI::printGradient("\n[3] PAQUETES POR PRECIO (MAYOR A MENOR)", Paletas::Exito, false);
    ColorUI::printGradient("\n[4] PAQUETES POR PRESUPUESTO", Paletas::Exito, false);
    ColorUI::printGradient("\n[5] VER TODOS LOS PAQUETES", Paletas::Exito, false);
    ColorUI::printGradient("\n[0] SALIR", Paletas::Exito, false);
    
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
            cout << "\n\n> Ingrese opcion (0 para cancelar): ";
            int sel = LeerOpcion();
            if (sel <= 0) { break; }
            if (sel <= (int)origenes.size()) {
                string origen = origenes[sel-1];
                principal->ConsultarCatalogoDinamico<Paquete>(
                    paquetes, 
                    "PAQUETES CON ORIGEN EN: " + origen,
                    [origen](Paquete* p){ return p->getVueloIncluido()->getOrigen() == origen; }
                );
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
            cout << "\n\n> Ingrese opcion (0 para cancelar): ";
            int sel = LeerOpcion();
            if (sel <= 0) { break; }
            if (sel <= (int)destinos.size()) {
                string destino = destinos[sel-1];
                principal->ConsultarCatalogoDinamico<Paquete>(
                    paquetes, 
                    "PAQUETES HACIA: " + destino,
                    [destino](Paquete* p){ return p->getVueloIncluido()->getDestino() == destino; }
                );
            } else {
                ColorUI::Alertas::MostrarError("Opcion invalida.");
            }
            pausarConsola();
            break;
        }
        case '3': {
            DibujarHeader("Inicio > Catalogo > Paquetes > Por Precio");
            Lista<Paquete*>* aux= principal->getControladorPaquetes()->getPaquetes();
            aux->QuickSort([](Paquete* p1, Paquete* p2){return p1->getPrecioBase()<p2->getPrecioBase();});
            principal->ConsultarCatalogoDinamico<Paquete>(aux,"PAQUETES DE MENOR A MAYOY PRECIO",[](Paquete* p){return true;});
            pausarConsola();
            break;
        }
        case '4': {
            DibujarHeader("Inicio > Catalogo > Paquetes > Por Presupuesto");
            float presupuesto;
            ColorUI::printGradient("\nDIGITE EL PRESUPUESTO: ", Paletas::Exito, false, false); 
            cin >> presupuesto; cin.ignore();
            
            // Implementación dinámica
            principal->ConsultarCatalogoDinamico<Paquete>(
                principal->getControladorPaquetes()->getPaquetes(),
                "PAQUETES HASTA: $" + to_string(presupuesto),
                [presupuesto](Paquete* p){ return p->getPrecioBase() <= presupuesto; }
            );
            pausarConsola();
            break;
        }
        case '5': {
            DibujarHeader("Inicio > Catalogo > Paquetes > Todos");
            principal->ConsultarCatalogoDinamico<Paquete>(
                principal->getControladorPaquetes()->getPaquetes(),
                "TODOS LOS PAQUETES PROMOCIONALES",
                [](Paquete* p){ return true; }
            );
            break;
        }
        case '0': historialPantallas->desapilar(); break;
    }
}

void GestionPantallas::HistorialReservas() {
    historialPantallas->desapilar();
    historialPantallas->apilar(PANTALLA_FILTROS_RESERVAS);
}

void GestionPantallas::MenuDatosUsuario(){
    DibujarHeader("Inicio > Mis Datos");
    Lista<Usuario*>* aux= new Lista<Usuario*>();
    aux->agregaFinal(principal->getControladorUsuarios()->gettablaUsuarios()->Buscar(userActual->getCorreo()));
    principal->ConsultarCatalogoDinamico<Usuario>(aux,"DATOS DEL USUARIO",[](Usuario* u){return true;}); 
    pausarConsola();
    historialPantallas->desapilar();
}

void GestionPantallas::MenuCancelarReserva() {
    DibujarHeader("Inicio > Cancelar Reserva");
    
    if (userActual->getReservas()->longitud() == 0) {
        cout << "No hay reservas registradas a su nombre" << endl;
        pausarConsola();
        historialPantallas->desapilar();
        return;
    }
    
    principal->ConsultarCatalogoDinamico<Reserva>(
        userActual->getReservas(), 
        "TUS RESERVAS ACTIVAS", 
        [](Reserva* r){ return true; }
    );
    
    ColorUI::printGradient("\nDIGITE EL ID (INDICE) DE LA RESERVA A CANCELAR\n", Paletas::Exito, false);
    int id = LeerOpcion();
    
    if (principal->CancelarReservaUsuario(userActual->getCodigo(), id)) {
        ColorUI::printGradient("\nEL MONTO SE REEMBOLSARA EN SU CUENTA MAXIMO 10 DIAS HABILES", Paletas::Exito, false);
    } else {
        ColorUI::printGradient("\nError al cancelar la reserva.", Paletas::Alerta, false);
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

    principal->ConsultarCatalogoDinamico<Hotel>(hoteles,"HOTELES EN : "+ciudad,[ciudad](Hotel* h){return h->getCiudad()==ciudad;});
    
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
    Lista<CiudadID*>* ciudades = principal->getControladorRutas()->getMapaCiudades();
    for(int i = 0; i < ciudades->longitud(); i++) {
        string c = ciudades->obtenerPos(i)->getNombre();
        bool existe = false;
        for(string& org : origenes) { if(org == c) existe = true; }
        if(!existe) origenes.push_back(c);
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
    for(int i = 0; i < ciudades->longitud(); i++) {
        string d = ciudades->obtenerPos(i)->getNombre();
        if (d != origen) {
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

    principal->ConsultarCatalogoDinamico<Hotel>(hoteles,"HOTELES EN: "+ciudad,[ciudad](Hotel* h){return h->getCiudad()==ciudad;});
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
    principal->ConsultarCatalogoDinamico<Paquete>(paquetes,"PAQUETES CON VUELO HACIA: "+ciudad,[ciudad](Paquete* p){return p->getVueloIncluido()->getDestino()==ciudad;});
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

    // --- Mapa visual de asientos del vuelo incluido ---
    Vuelo* vueloInc = principal->getControladorPaquetes()->getPaquetes()->obtenerPos(idPaquete)->getVueloIncluido();
    LimpiarConsola();
    ColorUI::printGradient("=== SELECCION DE ASIENTO (Vuelo del Paquete) ===", TemaPrincipal, false);
    cout << "\n\tMAPA DE ASIENTOS DEL VUELO: " << vueloInc->getOrigen() << " -> " << vueloInc->getDestino() << "\n\n";
    for (int i = 1; i <= 30; i++) {
        bool disponible = vueloInc->VerificarAsiento(i);
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
        if (vueloInc->VerificarAsiento(asiento)) {
            asientoValido = true;
        }
        else {
            ColorUI::printGradient("El asiento seleccionado no existe o ya esta ocupado.", Alerta, false);
        }
    }

    // --- Seleccion de clase con menú explícito ---
    LimpiarConsola();
    ColorUI::printGradient("=== SELECCION DE CLASE DE VUELO ===\n", TemaPrincipal, false);
    ColorUI::printGradient("\n\t[1] ECONOMICA", Exito, false);
    ColorUI::printGradient("\n\t[2] PREMIUM", Exito, false);
    ColorUI::printGradient("\n\t[3] EJECUTIVA", Exito, false);
    ColorUI::printGradient("\n\t[4] PRIMERA CLASE", Exito, false);
    ColorUI::printGradient("\n\nIngresa que clase deseas adquirir (1-4): ", Exito, false, false);
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
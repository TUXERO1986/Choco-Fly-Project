#include "GestionPantallas.h"
#include <iostream>
#include "Windows.h"

using namespace std;
using namespace ColorUI;


GestionPantallas::GestionPantallas(ControladorPrincipal* ptrPrincipal, Usuario* ptrUsuario) {
    principal = ptrPrincipal;
    userActual = ptrUsuario;
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

void GestionPantallas::Menuprincipal() {
    char opcion;
    do {
        system("cls");
        cout << BLINK;
        ColorUI::printGradient(chocofly, TemaPrincipal, false);
        cout << RESET;
        ColorUI::printGradient("\n\n\t\t\t\t\t[1] Consultar Vuelos", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[2] Catalogo Hospedaje", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[3] Paquetes Turisticos", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[4] Comprar Tickets", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[5] Mi Historial de Reservas", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[6] Creditos", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[7] Cerrar Sesion", Exito, false);

        opcion = _getch();

        switch (opcion) {
        case '1': system("cls"); VuelosRyan(); break;
        case '2': system("cls"); ReservarHospedaje(); break;
        case '3': system("cls"); CatalogoPaquetes(); break;
        case '4': system("cls"); GestionTickets(); break;
        case '5': system("cls"); HistorialReservas(); break;
        case '6': system("cls"); creditos(); break;
        case '7':
            system("cls");
            ColorUI::printGradient("Cerrando sesion...", gege, false);
            system("cls");
            RegisterScreen(principal);
            break;
        default: cout << "Opcion no valida" << endl; break;
        }
    } while (opcion != '7');
}

void GestionPantallas::VuelosRyan() {
    string origen, destino;
    system("cls");
    ColorUI::printGradient("=======================================================================", Paletas::TemaPrincipal, false);
    for (int i = 0; i < 12; i++) {
        ColorUI::printGradient("|                                  |                                  |", Paletas::TemaPrincipal, false);
    }
    ColorUI::printGradient("=======================================================================", Paletas::TemaPrincipal, false);

    gotoxy(38, 1); ColorUI::printGradient("CIUDADES DISPONIBLES:", Paletas::Exito, false);
    Lista<CiudadID*>* ciudades = principal->getControladorRutas()->getMapaCiudades();
    for (int i = 0; i < ciudades->longitud() && i < 10; i++) {
        gotoxy(38, 3 + i);
        cout << "[>] " << ciudades->obtenerPos(i)->getNombre();
    }

    gotoxy(2, 1); ColorUI::printGradient("BUSCADOR DE VUELOS", Paletas::TemaPrincipal, false);
    gotoxy(2, 3); cout << "(Ingresa '0' para salir)";

    gotoxy(2, 5); ColorUI::printGradient("Origen: ", Paletas::Exito, false, false);
    getline(cin, origen);
    if (origen == "0") return;

    gotoxy(2, 7); ColorUI::printGradient("Destino: ", Paletas::Alerta, false, false);
    getline(cin, destino);
    if (destino == "0") return;

    gotoxy(0, 15);
    cout << "\n";
    principal->ConsultarVuelos(origen, destino);
    cout << "\n";
    system("pause");
}

void GestionPantallas::ReservarHospedaje() {
    string ciudad;
    int idHotel, noches, habitacion, tipoO, tipoC, tipoS;

    ColorUI::printGradient("=== RESERVA DE HOTELES ===", Paletas::TemaPrincipal, false);
    ColorUI::printGradient("\nIngrese la ciudad destino para buscar hoteles:\nCiudad: ", Paletas::Exito, false, false);
    getline(cin, ciudad);

    cout << "\n";
    principal->FiltrarHotelesPorCiudad(ciudad);

    ColorUI::printGradient("\n================================", Paletas::Tux, false);
    ColorUI::printGradient("\nIngresa el ID del hotel que deseas reservar (o -1 para salir): ", Paletas::Exito, false, false);
    idHotel = LeerOpcion();
    if (idHotel == -1) return;

    if (idHotel < 0 || idHotel >= principal->getControladorHoteles()->getHoteles()->longitud()) {
        ColorUI::printGradient("ID de hotel invalido.", Paletas::Alerta, false);
        system("pause");
        return;
    }

    system("cls");
    cout << "\n\tMAPA DE HABITACIONES DEL HOTEL\n\n";

    for (int i = 1; i <= 30; i++) {
        bool disponible = principal->VerificarHabitacion(i, idHotel);

        string textoHab = "[";
        if (i < 10) textoHab += "0";
        textoHab += to_string(i) + "]";

        if (disponible) {
            ColorUI::printGradient(textoHab, Paletas::Register, false, false); 
        }
        else {
            ColorUI::printGradient("[XX]", Paletas::Alerta, false, false); 
        }

        if (i % 5 == 0) cout << "\n\n";
        else cout << "   ";
    }

    ColorUI::printGradient("\n\nNumero de habitacion deseada: ", Paletas::Exito, false, false);
    habitacion = LeerOpcion();

    ColorUI::printGradient("Cantidad de noches: ", Paletas::Exito, false, false);
    noches = LeerOpcion();

    tipoO = 1; tipoC = 1; tipoS = 1;

    principal->ReservarHotel(idHotel, userActual, noches, habitacion, tipoO, tipoC, tipoS);

    system("cls");
    ColorUI::printGradient("RESERVA DE HOTEL COMPLETADA", Paletas::gege, false);
    cout << "\n";
    system("pause");
}

void GestionPantallas::CatalogoPaquetes() {
    string ciudad;
    int idPaquete, noches, equipajeIda, equipajeRetorno, asiento, clase;

    ColorUI::printGradient("=== RESERVA DE PAQUETES TURISTICOS ===", Paletas::TemaPrincipal, false);
    ColorUI::printGradient("\nIngrese la ciudad destino:\nCiudad: ", Paletas::Exito, false, false);
    getline(cin, ciudad);

    cout << "\n";
    principal->FiltrarPaquetesPorDestino(ciudad);

    ColorUI::printGradient("\n================================", Paletas::Tux, false);
    ColorUI::printGradient("\nIngresa el ID del paquete que deseas comprar (o -1 para salir): ", Paletas::Exito, false, false);
    idPaquete = LeerOpcion();
    if (idPaquete == -1) return;

    // VALIDACIÓN ANTI-CRASH
    if (idPaquete < 0 || idPaquete >= principal->getControladorPaquetes()->getPaquetes()->longitud()) {
        ColorUI::printGradient("ID de paquete invalido. Abortando compra...", Paletas::Alerta, false);
        system("pause");
        return;
    }

    ColorUI::printGradient("Cantidad de noches de estadia: ", Paletas::Exito, false, false);
    noches = LeerOpcion();

    ColorUI::printGradient("Kilos de equipaje para la IDA: ", Paletas::Exito, false, false);
    equipajeIda = LeerOpcion();

    ColorUI::printGradient("Kilos de equipaje para el RETORNO: ", Paletas::Exito, false, false);
    equipajeRetorno = LeerOpcion();

    ColorUI::printGradient("Numero de asiento preferido: ", Paletas::Exito, false, false);
    asiento = LeerOpcion();

    clase = 1;

    principal->ReservarPaquete(idPaquete, userActual, noches, equipajeIda, equipajeRetorno, clase, asiento);

    system("cls");
    ColorUI::printGradient("PAQUETE COMPRADO CON EXITO", Paletas::gege, false);
    cout << "\n";
    system("pause");
}

void GestionPantallas::GestionTickets() {
    int indiceVuelo, equipaje, cabina, asiento, clase;
    string origen, destino, nombre;

    ColorUI::printGradient("=== COMPRA DE TICKETS ===", Paletas::TemaPrincipal, false);

    ColorUI::printGradient("\nOrigen: ", Exito, false, false);
    getline(cin, origen);
    if (origen == "0") return;
    ColorUI::printGradient("Destino: ", Alerta, false, false);
    getline(cin, destino);

    cout << "\n";
    principal->ConsultarVuelos(origen, destino);

    ColorUI::printGradient("================================", Tux, false);
    ColorUI::printGradient("\nIngresa el ID del vuelo que deseas reservar (o -1 para salir): ", Exito, false, false);
    indiceVuelo = LeerOpcion();

    if (indiceVuelo == -1) return;

    if (indiceVuelo < 0 || indiceVuelo >= principal->getControladorVuelos()->getVuelos()->longitud()) {
        ColorUI::printGradient("ID de vuelo invalido. Abortando compra...", Paletas::Alerta, false);
        system("pause");
        return;
    }

    system("cls");
    ColorUI::printGradient("=== SELECCION DE ASIENTO ===", Paletas::TemaPrincipal, false);
    cout << "\n\tMAPA DE ASIENTOS DEL VUELO\n\n";
    for (int i = 1; i <= 30; i++) {
        bool disponible = principal->VerificarAsiento(i, indiceVuelo);
        string textoAsiento = "[";
        if (i < 10) textoAsiento += "0";
        textoAsiento += to_string(i) + "]";

        if (disponible) {
            ColorUI::printGradient(textoAsiento, Paletas::Exito, false, false); 
        }
        else {
            ColorUI::printGradient("[XX]", Paletas::Alerta, false, false); 
        }

        if (i % 6 == 0) {
            cout << "\n\n"; 
        }
        else if (i % 3 == 0) {
            ColorUI::printGradient("   ||   ", Paletas::TemaPrincipal, false, false); 
        }
        else {
            cout << " "; 
        }
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

    system("cls");
    ColorUI::printGradient("Ingrese el nombre del pasajero principal: ", Exito, false, false);
    getline(cin, nombre);

    cout << endl;
    ColorUI::printGradient("Ingresa el peso del equipaje que llevaras en bodega (en kilos): ", Exito, false, false);
    equipaje = LeerOpcion();

    cout << endl;
    ColorUI::printGradient("Ingresa cuantas maletas de cabina llevaras: ", Exito, false, false);
    cabina = LeerOpcion();

    clase = 1;

    principal->ComprarTicket(indiceVuelo, userActual, equipaje, cabina, asiento, clase);

    system("cls");
    ColorUI::printGradient("TICKET COMPRADO CON EXITO", gege, false);
    ColorUI::printGradient("El asiento [" + to_string(asiento) + "] ha sido reservado para " + nombre, Exito, false);
    cout << "\n";
    system("pause");
}

void GestionPantallas::HistorialReservas() {
    ColorUI::printGradient("=== MI HISTORIAL DE RESERVAS ===", Paletas::TemaPrincipal, false);
    principal->MostrarReservasUsuario(userActual);
    cout << "\n";
    system("pause");
}
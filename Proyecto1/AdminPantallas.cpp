#include "AdminPantallas.h"
#include <iostream>
#include "Windows.h"

using namespace std;
using namespace ColorUI;

AdminPantallas::AdminPantallas(ControladorPrincipal* ptrPrincipal) {
    principal = ptrPrincipal;
}

/*
nota para ryan, leeropcion() es por si se pone un numero en vez de un string, a lo mejor sirva
*/
int AdminPantallas::LeerOpcion() {
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(1000, '\n');
        ColorUI::printGradient("\tError: Ingresa un numero valido: ", Alerta, false, false);
    }
    cin.ignore(1000, '\n');
    return x;
}

void AdminPantallas::MenuPrincipalAdmin() {
    char opcion;
    do {
        system("cls");
        cout << BLINK;
        ColorUI::printGradient(PanelControlADM, Tux, false);
        cout << RESET;
        gotoxy(0, 8);
        ColorUI::printGradient("\n\n\t\t\t\t\t[1] Reportes y Base de Datos", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[2] Mantenimiento (Agregar Datos)", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[3] Generacion Masiva de Datos", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[4] Cerrar Sesion", Alerta, false);

        opcion = _getch();

        switch (opcion) {
        case '1': MenuReportes(); break;
        case '2': MenuMantenimiento(); break;
        case '3': GenerarDatosAleatorios(); break;
        case '4':
            system("cls");
            RegisterScreen(principal);
            break;
        default: break;
        }
    } while (opcion != '4');
}

void AdminPantallas::MenuReportes() {
    char opcion;
    do {
        system("cls");
        ColorUI::printGradient(reportesADM, MoradoD, false);
        gotoxy(0, 8);
        cout << endl;
        ColorUI::printGradient("\n\t\t[1] Ver todos los Vuelos", Exito, false);
        ColorUI::printGradient("\n\t\t[2] Ver todos los Hoteles", Exito, false);
        ColorUI::printGradient("\n\t\t[3] Ver todos los Paquetes", Exito, false);
        ColorUI::printGradient("\n\t\t[4] Ver todas las Rutas", Exito, false);
        ColorUI::printGradient("\n\t\t[5] Ver TODAS las Reservas", Exito, false);
        ColorUI::printGradient("\n\t\t[6] Ver Usuarios Registrados", Exito, false);
        ColorUI::printGradient("\n\t\t[7] Ver Ingresos Totales", Exito, false);
        ColorUI::printGradient("\n\t\t[0] Volver", Alerta, false);

        opcion = _getch();
        system("cls");

        switch (opcion) {
        case '1': principal->MostrarVuelos(); system("pause"); break;
        case '2': principal->MostrarHoteles(); system("pause"); break;
        case '3': principal->MostrarPaquetes(); system("pause"); break;
        case '4': principal->MostrarRutas(); system("pause"); break;
        case '5': principal->MostrarReservas(); system("pause"); break;
        case '6': principal->MostrarUsuarios(); system("pause"); break;
        case '7':
            principal->ObtenerIngresosTotales();
            cout << "\n";
            system("pause");
            break;
        case '0': return;
        }
    } while (true);
}

void AdminPantallas::MenuMantenimiento() {
    char opcion;
    do {
        system("cls");
        ColorUI::printGradient(mantenimiento, MoradoD, false);
        gotoxy(0, 8);
        ColorUI::printGradient("\n\t\t\t[1] Agregar Vuelo Nuevo", Exito, false);
        ColorUI::printGradient("\n\t\t\t[2] Agregar Hotel Nuevo", Exito, false);
        ColorUI::printGradient("\n\t\t\t[3] Agregar Ruta Nueva", Exito, false);
        ColorUI::printGradient("\n\t\t\t[4] Eliminar un Registro (Vuelo/Hotel/etc)", Alerta, false);
        ColorUI::printGradient("\n\t\t\t[0] Volver al Menu Principal", Alerta, false);

        opcion = _getch();
        system("cls");

        switch (opcion) {
        case '1': {
            string origen, destino, escalas, fecha;
            float distancia;

            ColorUI::printGradient("\t=== NUEVO VUELO ===", TemaPrincipal, false);

            ColorUI::printGradient("\n\tOrigen: ", Exito, false, false);
            getline(cin, origen);
            ColorUI::printGradient("\tDestino: ", Exito, false, false);
            getline(cin, destino);
            ColorUI::printGradient("\tEscalas (Ej. 'Directo' o 'Lima-Bogota'): ", Exito, false, false);
            getline(cin, escalas);
            ColorUI::printGradient("\tFecha (Ej. 15-05-2026): ", Exito, false, false);
            getline(cin, fecha);
            ColorUI::printGradient("\tDistancia en KM: ", Exito, false, false);

            while (!(cin >> distancia)) {
                cin.clear();
                cin.ignore(1000, '\n');
                ColorUI::printGradient("\tError: Ingrese un numero valido para la distancia: ", Alerta, false, false);
            }
            cin.ignore(1000, '\n');

            principal->AgregarVuelo(origen, destino, escalas, fecha, distancia);

            cout << "\n";
            ColorUI::printGradient("\tVuelo agregado exitosamente a la base de datos.\n", gege, false);
            system("pause");
        } break;

        case '2': {
            string nombre, ciudad;
            float puntuacion, precio;

            ColorUI::printGradient("\t=== NUEVO HOTEL ===", TemaPrincipal, false);

            ColorUI::printGradient("\n\tNombre del Hotel: ", Exito, false, false);
            getline(cin, nombre);
            ColorUI::printGradient("\tCiudad: ", Exito, false, false);
            getline(cin, ciudad);

            ColorUI::printGradient("\tPuntuacion (Ej. 4.5): ", Exito, false, false);
            while (!(cin >> puntuacion)) {
                cin.clear(); cin.ignore(1000, '\n');
                ColorUI::printGradient("\tError: Ingrese un numero valido: ", Alerta, false, false);
            }

            ColorUI::printGradient("\tPrecio por noche: $", Exito, false, false);
            while (!(cin >> precio)) {
                cin.clear(); cin.ignore(1000, '\n');
                ColorUI::printGradient("\tError: Ingrese un numero valido: ", Alerta, false, false);
            }
            cin.ignore(1000, '\n');

            principal->AgregarHotel(nombre, ciudad, puntuacion, precio);

            cout << "\n";
            ColorUI::printGradient("\tHotel agregado exitosamente a la base de datos.\n", gege, false);
            system("pause");
        } break;

        case '3': {
            string origen, destino;
            float distancia;
            ColorUI::printGradient("\t=== NUEVA RUTA CONEXION ===", TemaPrincipal, false);
            ColorUI::printGradient("\n\tCiudad Origen: ", Exito, false, false);
            getline(cin, origen);
            ColorUI::printGradient("\tCiudad Destino: ", Exito, false, false);
            getline(cin, destino);
            ColorUI::printGradient("\tDistancia (Km): ", Exito, false, false);
            distancia = LeerOpcion();

            principal->AgregarRuta(origen, destino, distancia);
            ColorUI::printGradient("\n\tRuta conectada exitosamente.\n", gege, false);
            system("pause");
        } break;

        case '4': {
            ColorUI::printGradient(eliminacion, Alerta, false);
            gotoxy(0, 8);
            ColorUI::printGradient("\n\t\t\tQue deseas eliminar?\n\t\t\t[1] Vuelo | [2] Hotel | [3] Usuario | [0] Cancelar\n\t\t\tOpcion: ", Exito, false, false);
            char delOpt = _getch();

            if (delOpt == '0') break;

            cout << "\n\n\t\t\tIngresa el ID numerico a eliminar: ";
            int idTarget = LeerOpcion();

            if (delOpt == '1') principal->EliminarVuelo(idTarget);
            else if (delOpt == '2') principal->EliminarHotel(idTarget);
            else if (delOpt == '3') principal->EliminarUsuario(idTarget);

            ColorUI::printGradient("\n\t\t\tRegistro eliminado (si el ID era valido).\n", gege, false);
            system("pause");
        } break;

        case '0': return;
        }
    } while (true);
}

void AdminPantallas::GenerarDatosAleatorios() {
    system("cls");
    ColorUI::printGradient(datos, dato, false);
    gotoxy(0, 8);
    cout << "\n\tEsta opcion llenara la base de datos con informacion de prueba.\n";
    cout << "\tPresiona '1' para confirmar o '0' para cancelar.\n";

    char confirmacion = _getch();
    if (confirmacion == '1') {
        principal->GenerarDatos(20, 20, 20);
        ColorUI::printGradient("\n\tDatos generados con exito!\n", gege, false);
    }
    else {
        ColorUI::printGradient("\n\tOperacion cancelada.\n", Alerta, false);
    }
    system("pause");
}
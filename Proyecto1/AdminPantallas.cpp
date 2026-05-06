#include "AdminPantallas.h"
#include "Windows.h"
using namespace std;
using namespace ColorUI;

AdminPantallas::AdminPantallas(ControladorPrincipal* ptrPrincipal) {
    principal = ptrPrincipal;
}


void AdminPantallas::MenuAdmin() {
    int opcion;

    do {
        system("cls");

        cout << BLINK;
        ColorUI::printGradient(chocoadmin, Tux, false);
        cout << RESET;
        ColorUI::printGradient("\n\n\t\t\t\t\t[1] Agregar Vuelos", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[2] Agregar Paquetes", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[3] Agregar Hoteles", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[4] Eliminar Vuelos", Alerta, false);
        ColorUI::printGradient("\n\t\t\t\t\t[5] Eliminar Paquetes", Alerta, false);
        ColorUI::printGradient("\n\t\t\t\t\t[6] Eliminar Hoteles", Alerta, false);
        ColorUI::printGradient("\n\t\t\t\t\t[7] Salir", rosa, false);

        cout << "\n\t\t\t\t\tOpcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1: {
            AgregarVuelos();
        }    break;
        case 2: {
            AgregarPaquetes();
        } break;
        case 3: {
            AgregarHoteles();
        } break;
        case 4: {
            EliminarVuelos();
        } break;
        case 5: {
            EliminarPaquetes();
        } break;
        case 6: {
            EliminarHoteles();
        } break;
        case 7: {
            system("cls");
            RegisterScreen(principal);
            
        }break;
        default:
            cout << "Opcion no valida." << endl;
            system("pause>nul");
            break;
        }

    } while (opcion != 7);
}

// ==========================================
// funciones de ryan sisisi
// ==========================================

void AdminPantallas::AgregarVuelos() {
    int cantidad;
    cout << "\nCantidad de vuelos aleatorios a generar: ";
    cin >> cantidad;
    principal->GenerarVuelos(cantidad);
    ColorUI::printGradient("Vuelos generados correctamente.", gege, false);
    system("pause>nul");
}

void AdminPantallas::AgregarPaquetes() {
    int cantidad;
    cout << "\nCantidad de paquetes aleatorios a generar: ";
    cin >> cantidad;
    principal->GenerarPaquetes(cantidad);
    ColorUI::printGradient("Paquetes generados correctamente.", gege, false);
    system("pause>nul");
}

void AdminPantallas::AgregarHoteles() {
    int cantidad;
    cout << "\nCantidad de hoteles aleatorios a generar: ";
    cin >> cantidad;
    principal->GenerarHoteles(cantidad);
    ColorUI::printGradient("Hoteles generados correctamente.", gege, false);
    system("pause>nul");
}

void AdminPantallas::EliminarVuelos() {
    int idEliminar;
    system("cls");
    ColorUI::printGradient("=== ELIMINAR VUELOS ===", Alerta, false);
    principal->MostrarVuelos();
    cout << "\nIngrese el ID del vuelo a eliminar: ";
    cin >> idEliminar;
    principal->EliminarVuelo(idEliminar);
    ColorUI::printGradient("Vuelo eliminado correctamente.", gege, false);
    system("pause>nul");
}

void AdminPantallas::EliminarPaquetes() {
    int idEliminar;
    system("cls");
    ColorUI::printGradient("=== ELIMINAR PAQUETES ===", Alerta, false);
    principal->MostrarPaquetes();
    cout << "\nIngrese el ID del paquete a eliminar: ";
    cin >> idEliminar;
    principal->EliminarPaquete(idEliminar);
    ColorUI::printGradient("Paquete eliminado correctamente.", gege, false);
    system("pause>nul");
}

void AdminPantallas::EliminarHoteles() {
    int idEliminar;
    system("cls");
    ColorUI::printGradient("=== ELIMINAR HOTELES ===", Alerta, false);
    principal->MostrarHoteles();
    cout << "\nIngrese el ID del hotel a eliminar: ";
    cin >> idEliminar;
    principal->EliminarHotel(idEliminar);
    ColorUI::printGradient("Hotel eliminado correctamente.", gege, false);
    system("pause>nul");
}
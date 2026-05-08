#include "GestionPantallas.h"
#include <iostream>
#include "Windows.h"
using namespace ColorUI;


GestionPantallas::GestionPantallas(ControladorPrincipal* ptrPrincipal) {
    principal = ptrPrincipal;
}

void GestionPantallas::Menuprincipal(GestionPantallas* ui) {
    
	char opcion;
    do {
        system("cls");
        cout << BLINK;
        ColorUI::printGradient(chocofly, TemaPrincipal, false);
        cout << RESET;
        ColorUI::printGradient("\n\n\t\t\t\t\t[1] Consultar Vuelos", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[2] Catalogo Hospedaje", Exito, false);
		ColorUI::printGradient("\n\t\t\t\t\t[3] Paquetes", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[4] Tickets", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[5] Creditos", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[6] Menu", Exito, false);
        ColorUI::printGradient("\n\t\t\t\t\t[7] Salir", Exito, false);
		opcion = _getch();
        cin.ignore();
        switch (opcion)
        {
        case '1': {
            system("cls");
            VuelosRyan();
        } break;

        case '2': {
            system("cls");
            ReservarHospedaje(); 
        } break;

        case '3': {
            system("cls");
            CatalogoPaquetes();
        } break;
        case '4': {
            system("cls");
            GestionTickets();
        } break;

        case '5': {
            system("cls");
            creditos();
        } break;
        case '6': {
            system("cls");
            RegisterScreen(principal); 
        }break;

        case '7': {
            system("cls");
            for (int i = 0; i < 4;i++) {

            ColorUI:printGradient("Saliendo en ", Alerta, false, false); cout << i << endl;
                Sleep(600);
            }
            cout << BLINK;
            ColorUI::printGradient("Muchas Gracias!", gege, false);
            exit(0);
        }  break;
        default: cout << "Opcion no valida" << endl; break;
        }
    } while (opcion != '6');
}



void GestionPantallas::VuelosRyan() {
    string origen, destino;
	ColorUI::printGradient("Origen: ", Exito, false,false );
	getline(cin, origen);
	ColorUI::printGradient("Destino: ", Alerta, false,false );
    getline(cin, destino);
    principal->ConsultarVuelos(origen, destino);
    system("pause");
	//cin.ignore();
}

void GestionPantallas::ReservarHospedaje() {

    ColorUI::printGradient("    CATALOGO DE HOTELES   ", Paletas::TemaPrincipal, false);
    cout << "\n";
    principal->MostrarHoteles();
    cout << "\n";
	system("pause");
}

void GestionPantallas::GestionTickets() {
    int indiceVuelo, equipaje, cabina;
    string nombre;
    ColorUI::printGradient("=== COMPRA DE TICKETS ===", Paletas::TemaPrincipal, false);
    cout << "\n";

    principal->MostrarVuelos();
	ColorUI::printGradient("================================", Tux, false);

	ColorUI::printGradient("Para comprar un ticket, primero ingresa el ID del vuelo que deseas reservar.", Exito, false);
    cin >> indiceVuelo;

    cin.ignore();
    system("cls");
	ColorUI::printGradient("Ingrese el nombre del pasajero principal", Exito, false);
    getline(cin, nombre);
    cout << endl;
	ColorUI::printGradient("Ahora ingresa el peso del equipaje que llevaras en bodega (en kilos)", Exito, false);
    cin >> equipaje;
    cout << endl;
	ColorUI::printGradient("Finalmente, ingresa cuantas maletas llevara", Exito, false);
    //ingresar condicion 
    cin >> cabina;
    //

    //principal->ComprarTicket(indiceVuelo, nombre, equipaje, cabina);
    cout << endl;
    system("cls");
    ColorUI::printGradient("TICKET COMPRADO CON EXITO", gege, false);
	ColorUI::printGradient("Detalles de tu compra:", Exito, false);
    //principal->MostrarTickets();

    system("pause");
}

void GestionPantallas::CatalogoPaquetes() {
    ColorUI::printGradient("=== CATALOGO DE PAQUETES TURISTICOS ===", Paletas::TemaPrincipal, false);
    std::cout << "\n";

    principal->MostrarPaquetes(); // Llamas a la lógica que ya existe

    std::cout << "\n";
    ColorUI::printGradient("Presione cualquier tecla para regresar...", Paletas::Exito, false);
    system("pause>nul");
}
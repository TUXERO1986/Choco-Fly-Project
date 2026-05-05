#include "Lista.h"
#include "Color.h"
#include "ControladorVuelos.h"
#include "GestionPantallas.h"
#include "conio.h"


void VuelosRyan() {
    cin.ignore();

    string origen, destino;
    ControladorVuelos* controlador = new ControladorVuelos();
    controlador->GenerarVuelos(50);

    cout << "Digite el origen: ";
    getline(std::cin, origen);
    cout << "Digite el destino: ";
    getline(std::cin, destino);

    controlador->GenerarVuelosConEscala(origen, destino);

    system("pause");
    delete controlador;
}
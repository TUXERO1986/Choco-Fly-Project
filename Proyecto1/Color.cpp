#include <iostream>
#include "Color.h"

using namespace std;
using namespace ColorUI;

void Menuprincipal() {


    cout << UNDERLINE ;
    ColorUI::printGradient("\t =================== ", femboy, false);
    ColorUI::printGradient("\t | Femboys Airline |", femboy, false);
    ColorUI::printGradient("\t =================== \n", femboy, false);
    cout << RESET;
    ColorUI::printGradient("[1] \u2554 Vuelos  ", gege, false, false);
    ColorUI::printGradient(" \t[2] Paquetes ", gege, false, false);
    ColorUI::printGradient(" \t[3] Hospedaje ", gege, false,false);
    cout << BLINK; 
    ColorUI::printGradient(" \t[4] Creditos ", gege, false, false);
    cout << RESET;

}

void PruebaColor() {
    cout << BLINK;
    ColorUI::printGradient("   === SISTEMA DE GESTION ===   ", Exito, false);
    cout << "\n";
    cout << RESET;
    cout << "1. Iniciar Sesion\n";
    cout << "2. Registrar Usuario\n";
    cout << "3. Salir\n";
    ColorUI::printGradient("Seleccione una opcion: ", gege, false);
}

void test() {
    cout << "hola";
}
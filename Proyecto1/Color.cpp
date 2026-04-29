#include <iostream>
#include "Color.h"
#include <conio.h>
using namespace std;
using namespace ColorUI;
ControladorRutas* controlador = new ControladorRutas();
void Menuprincipal() {
    char a;
    do {
		system("cls");
        cout << UNDERLINE;
        ColorUI::printGradient("\t =================== ", femboy, false);
        ColorUI::printGradient("\t | Femboys Airline |", femboy, false);
        ColorUI::printGradient("\t =================== \n", femboy, false);
        cout << RESET;
        ColorUI::printGradient("[1] Vuelos  ", gege, false, false);
        ColorUI::printGradient(" \t[2] Buscar Vuelos Disponibles ", gege, false, false);
        ColorUI::printGradient(" \t[3] Hospedaje ", gege, false, false);
        cout << BLINK;
        ColorUI::printGradient(" \t[4] Salir ", Alerta, false, false);
        cout << RESET;
        a = _getch();
        switch (a) {
        case '1':
        {
            system("cls");
            cout << "Vuelos disponibles:\n";
            controlador->MostrarTodasLasRutas();
            system("pause>0");
            break;
        }
        case '2': {
			system("cls");
			string origen, destino;
			cout << "Digite la ciudad de origen: ";
            getline(cin, origen);
			cout << "Digite la ciudad de destino: ";
            getline(cin, destino);
			string resultado = controlador->BuscarRutaMasCorta(origen, destino);
            cout << resultado;
            cin.ignore();
            system("pause>0");
			break;
        }
        case '4': {
            system("cls");
            creditos();
            system("pause>0");
			break;
        }
        }
    } while (a != '5');

}
void creditos() {
    cout << BLINK;
    string Creditos = R"(
        >>========================================<<
        ||   _____              _ _ _             ||
        ||  / ____|            | (_) |            ||
        || | |     _ __ ___  __| |_| |_ ___  ___  ||
        || | |    | '__/ _ \/ _` | | __/ _ \/ __| ||
        || | |____| | |  __/ (_| | | || (_) \__ \ ||
        ||  \_____|_|  \___|\__,_|_|\__\___/|___/ ||
        >>========================================<<
    )";
    ColorUI::printGradient(Creditos, femboy, false);
    cout << RESET;

    string ryan = R"(
      Ryan (apellido)
    [Programador C++ Backend]

            .--.
           |o_o |
           |:_/ |
          //   \ \
         (|     | )
        /'\_   _/`\
        \___)=(___/ 
    )";

    string gengis = R"(
      Gengis cam pizarro
    [Frontend Console App]

           ,_     _
           |\_,-~/
           / _  _ |    ,--.
          (  @  @ )   / ,-'
           \  _T_/-._( (
           /         `. \
          |         _  \ |
           \ \ ,  /      |
            || |-_\__   /
           ((_/`(____,-'
    )";

    string santiago = R"(
      Santiago (Apellido)
    [Correccion de Bugs]

               __         __
              /  \.-"""-./  \
              \    -   -    /
               |   o   o   |
               \  .-'''-.  /
                '-\__Y__/-'
                   `---`
    )";

    ColorUI::printMultilinesSideBySide(
        ryan, Tux,
        gengis, gege,
        santiago, TemaPrincipal
    );
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